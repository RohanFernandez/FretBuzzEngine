#include <fretbuzz_pch.h>
#include "system/system_defines.h"
#include "rect_collider.h"
#include "system/game_object_2d.h"
#include "system/core/input.h"
#include "system/core/resource_manager.h"
#include "graphics/shader_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		RectCollider::RectCollider(GameObject2D& a_GameObject, glm::vec2 a_v2Dimensions, PhysicsEngine::PHYSICS_BODY_TYPE a_PhysicsBodyType, bool a_bIsFixedRotation, bool a_bIsBullet)
			: IComponent2D(COMPONENT_TYPE::RECT_COLLIDER, a_GameObject),
#ifdef _IS_DEBUG_RENDERING
			ns_graphics::IRenderer(),
#endif
			m_PhysicsBodyType{ a_PhysicsBodyType},
			m_bIsFixedRotation{ a_bIsFixedRotation },
			m_v2DimensionWH{ a_v2Dimensions }
		{
#ifdef _IS_DEBUG_RENDERING
			m_Material.setShader(*ns_graphics::ShaderManager::getShaderOfType(ns_graphics::Shader::DEFAULT_LINE));
#endif
			b2BodyDef l_bodyDef;
			l_bodyDef.bullet = a_bIsBullet;

			l_bodyDef.type = (m_PhysicsBodyType == PhysicsEngine::PHYSICS_BODY_TYPE::STATIC) ?
				b2_staticBody : (m_PhysicsBodyType == PhysicsEngine::PHYSICS_BODY_TYPE::DYNAMIC) ?
				b2_dynamicBody : b2_kinematicBody;
			glm::vec2 l_Position = m_GameObject.m_Transform.getWorldPosition();
			l_bodyDef.position.Set(l_Position.x, l_Position.y);
			l_bodyDef.angle = m_GameObject.m_Transform.getLocalRotation().z;
			l_bodyDef.fixedRotation = m_bIsFixedRotation;

			m_pBody = PhysicsEngine::getB2World()->CreateBody(&l_bodyDef);
			
			b2PolygonShape l_boxShape;
			l_boxShape.SetAsBox(m_v2DimensionWH.x * 0.5f, m_v2DimensionWH.y * 0.5f);

			b2FixtureDef l_fixtureDef;
			l_fixtureDef.shape = &l_boxShape;
			l_fixtureDef.density = (m_PhysicsBodyType == PhysicsEngine::PHYSICS_BODY_TYPE::STATIC) ? 0.0f : 1.0f;
			l_fixtureDef.friction = 0.0f;
			m_pFixture = m_pBody->CreateFixture(&l_fixtureDef);

#ifdef _IS_DEBUG_RENDERING

			//Setup rect collider borders using LineData for debugging
			float l_fLeftX = m_v2DimensionWH.x * -0.5f;
			float l_fRightX = m_v2DimensionWH.x * 0.5f;
			float l_fTopY = m_v2DimensionWH.y * 0.5f;
			float l_fBottomY = m_v2DimensionWH.y * -0.5f;

			m_arrRectLineBorders[0] = 
				ns_graphics::LineData
					{ 
						{ l_fLeftX, l_fBottomY ,0.0f, 1.0f},
						{0.0f, 0.0f ,1.0f, 1.0f },
						{ l_fRightX, l_fBottomY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f }
					};

			m_arrRectLineBorders[1] =
				ns_graphics::LineData
					{
						{ l_fRightX, l_fBottomY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f },
						{ l_fRightX, l_fTopY, 0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f }
					};

			m_arrRectLineBorders[2] =
				ns_graphics::LineData
					{
						{ l_fRightX, l_fTopY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f },
						{ l_fLeftX, l_fTopY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f }
					};

			m_arrRectLineBorders[3] =
				ns_graphics::LineData
					{
						{ l_fLeftX, l_fTopY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f },
						{ l_fLeftX, l_fBottomY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f }
					};

#endif
		}

		RectCollider::~RectCollider()
		{
			PhysicsEngine::getB2World()->DestroyBody(m_pBody);
		}

		void RectCollider::onEnable()
		{
			glm::vec2 l_v2WorldPosition = m_GameObject.m_Transform.getWorldPosition();
			m_pBody->SetTransform({ l_v2WorldPosition.x, l_v2WorldPosition.y }, m_GameObject.m_Transform.getLocalRotation().z);
			m_pBody->SetActive(true);
		}

		void RectCollider::onDisable()
		{
			m_pBody->SetActive(false);
		}	

		RectCollider* RectCollider::addToGameObject(GameObject2D& a_GameObject, glm::vec2 a_v2DimensionWH,
			PhysicsEngine::PHYSICS_BODY_TYPE a_PhysicsBodyType, bool a_bIsFixedRotation, bool a_bIsBullet)
		{
			return IComponent::isComponentOfTypeExistInGameObj(COMPONENT_TYPE::RECT_COLLIDER, &a_GameObject) ?
				nullptr : new RectCollider(a_GameObject, a_v2DimensionWH, a_PhysicsBodyType, a_bIsFixedRotation, a_bIsBullet);
		}

		RectCollider* RectCollider::addToGameObject(GameObject2D& a_GameObject, PhysicsEngine::PHYSICS_BODY_TYPE a_PhysicsBodyType, bool a_bIsFixedRotation, bool a_bIsBullet)
		{
			return IComponent::isComponentOfTypeExistInGameObj(COMPONENT_TYPE::RECT_COLLIDER, &a_GameObject) ?
				nullptr : new RectCollider(a_GameObject, a_GameObject.m_RectTransform.getRect().m_v2DimensionsWH , a_PhysicsBodyType, a_bIsFixedRotation, a_bIsBullet);
		}

		void RectCollider::update(float a_fDeltaTime)
		{
			//Set transform position from collider position.
			const b2Vec2& l_v2ColliderPosition = m_pBody->GetPosition();
			m_GameObject.m_Transform.setWorldPosition({ l_v2ColliderPosition.x, l_v2ColliderPosition.y, m_GameObject.m_Transform.getWorldPosition().z });

			if (Input::IsKeyPutDown(GLFW_KEY_V))
			{
				std::cout << "ColliderPosition:: {" << l_v2ColliderPosition.x << "," << l_v2ColliderPosition.y << "}\n";
			}

			//Set transform rotation from collider rotation if the collider's rotation is not fixed.
			if (!m_bIsFixedRotation)
			{
				glm::quat l_quatTransformRotation = m_GameObject.m_Transform.getLocalRotation();
				m_GameObject.m_Transform.setLocalRotation({ l_quatTransformRotation.x , l_quatTransformRotation.y , m_pBody->GetAngle() });
			}
		}

		void RectCollider::applyForce(b2Vec2 a_v2ForceDirection)
		{
			m_pBody->ApplyForceToCenter(a_v2ForceDirection, true);
		}

		void RectCollider::setLinearVelocity(b2Vec2 a_v2VelocityDirection)
		{
			m_pBody->SetLinearVelocity(a_v2VelocityDirection);
		}

		void RectCollider::applyImpulse(b2Vec2 a_v2ForceDirection)
		{
			m_pBody->ApplyLinearImpulseToCenter(a_v2ForceDirection, true);
		}

		void RectCollider::debugRender(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera)
		{
#ifdef _IS_DEBUG_RENDERING
			ns_graphics::LineBatchRenderer::submit(m_arrRectLineBorders, 4, a_mat4Transformation, m_Material);
#endif
		}
	}
}