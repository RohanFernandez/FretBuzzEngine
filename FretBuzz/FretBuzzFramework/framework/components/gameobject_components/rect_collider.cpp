#pragma once
#include "../../system/core/system_defines.h"
#include "rect_collider.h"
#include "../../system/game_object.h"
#include <iostream>
#include "../../system/core/input.h"
#include "../../system/core/resource_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		RectCollider::RectCollider(GameObject& a_GameObject, glm::vec2 a_v2Dimensions, bool a_bIsStatic, bool a_bIsFixedRotation)
			: IComponent(COMPONENT_TYPE::RECT_COLLIDER, a_GameObject),
			m_bIsStatic{ a_bIsStatic },
			m_bIsFixedRotation{ a_bIsFixedRotation },
			m_v2Dimensions{ a_v2Dimensions },
			m_pDefaultLineShader{ ResourceManager::getResource<ns_graphics::Shader>(ns_graphics::Shader::DEFAULT_LINE_SHADER_ID) }
		{
			b2BodyDef l_bodyDef;
			l_bodyDef.type = m_bIsStatic ? b2_staticBody : b2_dynamicBody;
			glm::vec2 l_Position = m_GameObject.m_Transform.getPosition();
			l_bodyDef.position.Set(l_Position.x, l_Position.y);
			l_bodyDef.angle = m_GameObject.m_Transform.getRotation().z;
			l_bodyDef.fixedRotation = m_bIsFixedRotation;

			m_pBody = PhysicsEngine::getB2World()->CreateBody(&l_bodyDef);
			
			b2PolygonShape l_boxShape;
			l_boxShape.SetAsBox(m_v2Dimensions.x / 2.0f, m_v2Dimensions.y / 2.0f);

			b2FixtureDef l_fixtureDef;
			l_fixtureDef.shape = &l_boxShape;
			l_fixtureDef.density = m_bIsStatic ? 0.0f : 1.0f;
			l_fixtureDef.friction = 0.0f;
			m_pFixture = m_pBody->CreateFixture(&l_fixtureDef);

#ifdef _IS_DEBUG_RENDERING

			//Setup rect collider borders using LineData for debugging
			float l_fLeftX = m_v2Dimensions.x * -0.5f;
			float l_fRightX = m_v2Dimensions.x * 0.5f;
			float l_fTopY = m_v2Dimensions.y * 0.5f;
			float l_fBottomY = m_v2Dimensions.y * -0.5f;

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
			m_pDefaultLineShader = nullptr;
		}

		RectCollider* RectCollider::addToGameObject(GameObject& a_GameObject, glm::vec2 a_v2Dimensions, bool a_bIsStatic, bool a_bIsFixedRotation)
		{
			return IComponent::isComponentOfTypeExistInGameObj(COMPONENT_TYPE::RECT_COLLIDER, &a_GameObject) ?
				nullptr : new RectCollider(a_GameObject, a_v2Dimensions, a_bIsStatic, a_bIsFixedRotation);
		}

		void RectCollider::update(float a_fDeltaTime)
		{
			//Set transform position from collider position.
			const b2Vec2& l_v2ColliderPosition = m_pBody->GetPosition();
			const glm::vec3& l_v3TransformPosition = m_GameObject.m_Transform.getPosition();		
			m_GameObject.m_Transform.translate({ l_v2ColliderPosition.x, l_v2ColliderPosition.y, l_v3TransformPosition.z });

			if (Input::IsKeyPutDown(GLFW_KEY_V))
			{
				std::cout << "ColliderPosition:: {" << l_v2ColliderPosition.x << "," << l_v2ColliderPosition.y << "}\n";
			}

			//Set transform rotation from collider rotation if the collider's rotation is not fixed.
			if (!m_bIsFixedRotation)
			{
				const float l_fColliderRotatedZAngle = m_pBody->GetAngle();
				const glm::vec3& l_v3TransformRotation = m_GameObject.m_Transform.getRotation();
				m_GameObject.m_Transform.rotate({ l_v3TransformRotation.x, l_v3TransformRotation.y , l_fColliderRotatedZAngle });
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

		void RectCollider::debugRender(const glm::mat4& a_mat4Transformation, const ns_system::Viewport& a_Camera)
		{
			ns_graphics::LineBatchRenderer::submit(m_arrRectLineBorders, 4, a_mat4Transformation, m_pDefaultLineShader);
		}
	}
}