#include <fretbuzz_pch.h>
#include "collider_2d.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		Collider2D::Collider2D(COMPONENT_TYPE a_ComponentType, GameObject2D& a_GameObject2D, ColliderData& a_ColliderData)
			: IComponent2D(a_ComponentType, a_GameObject2D),
			m_ColliderData{ a_ColliderData }
		{
			b2BodyDef l_bodyDef;
			l_bodyDef.bullet = m_ColliderData.m_bIsBullet;

			l_bodyDef.type = (m_ColliderData.m_PhysicsBodyType == PhysicsEngine::PHYSICS_BODY_TYPE::STATIC) ?
				b2_staticBody : (m_ColliderData.m_PhysicsBodyType == PhysicsEngine::PHYSICS_BODY_TYPE::DYNAMIC) ?
				b2_dynamicBody : b2_kinematicBody;

			glm::vec2 l_Position = m_GameObject.m_Transform.getWorldPosition();
			l_bodyDef.position.Set(l_Position.x, l_Position.y);
			l_bodyDef.angle = m_GameObject.m_Transform.getLocalRotation().z;
			l_bodyDef.fixedRotation = m_ColliderData.m_bIsFixedRotation;

			m_pBody = PhysicsEngine::getB2World()->CreateBody(&l_bodyDef);
			m_pBody->SetUserData(this);

			b2Shape* l_pb2Shape = nullptr;
			b2PolygonShape l_boxShape;
			b2CircleShape l_circleShape;

			if (m_ColliderData.m_ColliderShape == m_ColliderData.SHAPE_RECT)
			{
				glm::vec3 l_LocalScale = m_GameObject.m_Transform.getLocalScale();
				l_boxShape.SetAsBox(m_ColliderData.m_v2DimensionWH.x * l_LocalScale.x * 0.5f, m_ColliderData.m_v2DimensionWH.y * l_LocalScale.y * 0.5f);
				l_pb2Shape = &l_boxShape;
			}
			else if(m_ColliderData.m_ColliderShape == m_ColliderData.SHAPE_CIRCLE)
			{
				l_circleShape.m_p.Set(m_ColliderData.m_v2RelativePos.x, m_ColliderData.m_v2RelativePos.y);
				l_circleShape.m_radius = m_ColliderData.m_fRadius; 
				l_pb2Shape = &l_circleShape;
			}

			b2FixtureDef l_fixtureDef;
			l_fixtureDef.shape = l_pb2Shape;
			l_fixtureDef.density = (m_ColliderData.m_PhysicsBodyType == PhysicsEngine::PHYSICS_BODY_TYPE::STATIC) ? 0.0f : 1.0f;
			l_fixtureDef.friction = 0.0f;
			m_pFixture = m_pBody->CreateFixture(&l_fixtureDef);

			const std::vector<IComponent*>& l_vectComponents = m_GameObject.getAllComponents();
			for (auto l_CurrentComponent = l_vectComponents.begin(); l_CurrentComponent != l_vectComponents.end(); l_CurrentComponent++)
			{
				registerColliderEvent(*l_CurrentComponent);
			}
		};

		Collider2D::~Collider2D()
		{
			PhysicsEngine::getB2World()->DestroyBody(m_pBody);
		}

		void Collider2D::Update(float a_fDeltaTime)
		{
			if (m_ColliderData.m_PhysicsBodyType == PhysicsEngine::PHYSICS_BODY_TYPE::STATIC)
			{
				return;
			}

			//Set transform position from collider position.
			const b2Vec2& l_v2ColliderPosition = m_pBody->GetPosition();
			m_GameObject.m_Transform.setWorldPosition({ l_v2ColliderPosition.x, l_v2ColliderPosition.y, m_GameObject.m_Transform.getWorldPosition().z });

			//Set transform rotation from collider rotation if the collider's rotation is not fixed.
			if (!m_ColliderData.m_bIsFixedRotation)
			{
				glm::quat l_quatTransformRotation = m_GameObject.m_Transform.getLocalRotation();
				m_GameObject.m_Transform.setLocalRotation({ l_quatTransformRotation.x , l_quatTransformRotation.y , m_pBody->GetAngle() });
			}
		}

		void Collider2D::onEnable()
		{
			glm::vec2 l_v2WorldPosition = m_GameObject.m_Transform.getWorldPosition();
			m_pBody->SetTransform({ l_v2WorldPosition.x, l_v2WorldPosition.y }, m_GameObject.m_Transform.getLocalRotation().z);
			m_pBody->SetActive(true);
		}

		void Collider2D::onDisable()
		{
			m_pBody->SetActive(false);
		}

		void Collider2D::registerColliderEvent(IComponent* a_pIComponent)
		{
			CollisionEvents2D* l_pCollisionEvents2D = nullptr;
			l_pCollisionEvents2D = dynamic_cast<CollisionEvents2D*>(a_pIComponent);
			if (l_pCollisionEvents2D != nullptr)
			{
				m_lstRegisteredCollisionEvents.emplace_back(l_pCollisionEvents2D);
			}
		}

		void Collider2D::unregisterColliderEvent(IComponent* a_pIComponent)
		{
			CollisionEvents2D* l_pCollisionEvents2D = nullptr;
			l_pCollisionEvents2D = dynamic_cast<CollisionEvents2D*>(a_pIComponent);
			if (l_pCollisionEvents2D != nullptr)
			{
				auto l_FoundIterator = std::find(m_lstRegisteredCollisionEvents.begin(), m_lstRegisteredCollisionEvents.end(), l_pCollisionEvents2D);
				m_lstRegisteredCollisionEvents.erase(l_FoundIterator);
			}
		}

		void Collider2D::onSiblingComponentAdded(IComponent* a_pComponent)
		{
			registerColliderEvent(a_pComponent);
		}

		void Collider2D::onSiblingComponentRemoved(IComponent* a_pComponent)
		{
			unregisterColliderEvent(a_pComponent);
		}

		void Collider2D::applyForce(glm::vec2 a_v2ForceDirection)
		{
			m_pBody->ApplyForceToCenter(b2Vec2{ a_v2ForceDirection.x, a_v2ForceDirection.y }, true);
		}

		void Collider2D::setLinearVelocity(glm::vec2 a_v2VelocityDirection)
		{
			m_pBody->SetLinearVelocity(b2Vec2{ a_v2VelocityDirection.x, a_v2VelocityDirection.y });
		}

		void Collider2D::applyImpulse(glm::vec2 a_v2ForceDirection)
		{
			m_pBody->ApplyLinearImpulseToCenter(b2Vec2{ a_v2ForceDirection.x, a_v2ForceDirection.y }, true);
		}
	}
}