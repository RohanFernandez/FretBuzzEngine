#include <fretbuzz_pch.h>
#include "collider_2d.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		Collider2D::Collider2D(GameObject2D& a_GameObject2D, ColliderData& a_ColliderData)
			: IComponent2D(COMPONENT_TYPE::COLLIDER_2D, a_GameObject2D),
			m_ColliderData{ a_ColliderData }
		{
			b2BodyDef l_bodyDef;
			l_bodyDef.bullet = m_ColliderData.m_bIsBullet;

			l_bodyDef.type = (b2BodyType)m_ColliderData.m_PhysicsBodyType;

			glm::vec2 l_Position = m_GameObject.m_Transform.getWorldPosition();
			l_bodyDef.position.Set(l_Position.x, l_Position.y);
			l_bodyDef.angle = glm::eulerAngles(m_GameObject.m_Transform.getLocalRotation()).z;
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
			l_fixtureDef.isSensor = m_ColliderData.m_bIsSensor;
			l_fixtureDef.shape = l_pb2Shape;
			l_fixtureDef.filter.categoryBits = GetBitField(m_ColliderData.m_vectColliderCategoryBits);
			l_fixtureDef.filter.maskBits = GetBitField(m_ColliderData.m_vectColliderMaskBits);
			l_fixtureDef.filter.groupIndex = m_ColliderData.m_iGroupIndex;
			l_fixtureDef.density = m_ColliderData.m_fDensity;
			l_fixtureDef.friction = 0.0f;
			m_pFixture = m_pBody->CreateFixture(&l_fixtureDef);

			PhysicsEngine::getB2World()->SetContactListener(this);
		};

		Collider2D::~Collider2D()
		{
			b2World* l_pb2World = PhysicsEngine::getB2World();
		}

		void Collider2D::Update(float a_fDeltaTime)
		{
			if (m_ColliderData.m_PhysicsBodyType == PHYSICS_BODY_TYPE::DYNAMIC)
			{
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
			else if(m_ColliderData.m_PhysicsBodyType == PHYSICS_BODY_TYPE::KINEMATIC)
			{
				glm::vec2 l_v2WorldPosition = m_GameObject.m_Transform.getWorldPosition();
				m_pBody->SetTransform({ l_v2WorldPosition.x, l_v2WorldPosition.y }, glm::eulerAngles(m_GameObject.m_Transform.getLocalRotation()).z);
			}
		}

		void Collider2D::onEnable()
		{
			IComponent2D::onEnable();
			glm::vec2 l_v2WorldPosition = m_GameObject.m_Transform.getWorldPosition();
			m_pBody->SetTransform({ l_v2WorldPosition.x, l_v2WorldPosition.y }, m_GameObject.m_Transform.getLocalRotation().z);
			m_pBody->SetActive(true);
		}

		void Collider2D::onDisable()
		{
			IComponent2D::onDisable();
			m_pBody->SetActive(false);
		}

		void Collider2D::onSiblingComponentAdded(IComponent* a_pComponent)
		{
		}

		void Collider2D::onSiblingComponentRemoved(IComponent* a_pComponent)
		{
		}

		void Collider2D::applyForceToCenter(glm::vec2 a_v2ForceDirection)
		{
			m_pBody->ApplyForceToCenter(b2Vec2{ a_v2ForceDirection.x, a_v2ForceDirection.y }, true);
		}

		void Collider2D::applyForceAtPoint(glm::vec2 a_v2ForceDirection, glm::vec2 a_v2Point)
		{
			m_pBody->ApplyForce(b2Vec2{ a_v2ForceDirection.x,  a_v2ForceDirection.y }, m_pBody->GetWorldPoint(b2Vec2{ a_v2Point.x, a_v2Point.y }), true);
		}

		void Collider2D::setLinearVelocity(glm::vec2 a_v2VelocityDirection)
		{
			m_pBody->SetLinearVelocity(b2Vec2{ a_v2VelocityDirection.x, a_v2VelocityDirection.y });
		}

		void Collider2D::applyImpulseToCenter(glm::vec2 a_v2ForceDirection)
		{
			m_pBody->ApplyLinearImpulseToCenter(b2Vec2{ a_v2ForceDirection.x, a_v2ForceDirection.y }, true);
		}

		void Collider2D::applyImpulseAtPoint(glm::vec2 a_v2ForceDirection, glm::vec2 a_v2Point)
		{
			m_pBody->ApplyLinearImpulse(b2Vec2{ a_v2ForceDirection.x,  a_v2ForceDirection.y }, m_pBody->GetWorldPoint(b2Vec2{ a_v2Point.x, a_v2Point.y }), true);
		}

		void Collider2D::setAngularVelocity(float a_fAngularVelocity)
		{
			m_pBody->SetAngularVelocity(a_fAngularVelocity);
		}

		glm::vec2 Collider2D::getWorldCenterOfCollider()
		{
			b2Vec2 l_b2v2WorldCenter = m_pBody->GetWorldCenter();
			return glm::vec2{ l_b2v2WorldCenter.x, l_b2v2WorldCenter.y };
		}

#pragma region GETTERS AND SETTERS

		void Collider2D::setPhysicsBodyType(PHYSICS_BODY_TYPE a_PhysicsBodyType)
		{
			m_ColliderData.m_PhysicsBodyType = a_PhysicsBodyType;
			m_pBody->SetType((b2BodyType)a_PhysicsBodyType);
		}

		PHYSICS_BODY_TYPE Collider2D::getPhysicsBodyType()
		{
			return m_ColliderData.m_PhysicsBodyType;
		}

		void Collider2D::setSensor(bool a_bIsEnabled)
		{
			m_ColliderData.m_bIsSensor = a_bIsEnabled;
			m_pFixture->SetSensor(a_bIsEnabled);
		}

		bool Collider2D::isSensor() const
		{
			return m_ColliderData.m_bIsSensor;
		}

		void Collider2D::setFixedRotation(bool a_bIsFixedRotation)
		{
			m_ColliderData.m_bIsFixedRotation = a_bIsFixedRotation;
			m_pBody->SetFixedRotation(a_bIsFixedRotation);
		}

		bool Collider2D::getIsFixedRotation()
		{
			return m_ColliderData.m_bIsFixedRotation;
		}

		void Collider2D::setDensity(float a_fDensity)
		{
			m_ColliderData.m_fDensity = a_fDensity;
			m_pFixture->SetDensity(a_fDensity);
		}

		float Collider2D::getDensity()
		{
			return m_ColliderData.m_fDensity;
		}

		void Collider2D::setMaskBits(std::vector<uint16> a_vectMaskBits)
		{
			m_ColliderData.m_vectColliderMaskBits = a_vectMaskBits;
			b2Filter l_b2Filter;
			l_b2Filter.maskBits = GetBitField(m_ColliderData.m_vectColliderMaskBits);
			m_pFixture->SetFilterData(l_b2Filter);
		}

		std::vector<uint16> Collider2D::Collider2D::getMaskBits() const
		{
			return m_ColliderData.m_vectColliderMaskBits;
		}

		void Collider2D::setCategoryBits(std::vector<uint16> a_vectCategoryBits)
		{
			m_ColliderData.m_vectColliderCategoryBits = a_vectCategoryBits;
			b2Filter l_b2Filter;
			l_b2Filter.categoryBits = GetBitField(m_ColliderData.m_vectColliderCategoryBits);
			m_pFixture->SetFilterData(l_b2Filter);
		}

		std::vector<uint16> Collider2D::getCategoryBits() const
		{
			return m_ColliderData.m_vectColliderCategoryBits;
		}

		uint16 Collider2D::GetBitField(std::vector<uint16>& a_vectBits) const
		{
			uint16 l_Return = 0;
			for (auto l_CollliderBit = a_vectBits.begin(); l_CollliderBit != a_vectBits.end(); l_CollliderBit++)
			{
				l_Return |= *l_CollliderBit;
			}
			return l_Return;
		}

#pragma endregion GETTERS AND SETTERS

		void Collider2D::BeginContact(b2Contact* a_pContact)
		{
			Collider2D* l_pColliderA = static_cast<Collider2D*>(a_pContact->GetFixtureA()->GetBody()->GetUserData());
			Collider2D* l_pColliderB = static_cast<Collider2D*>(a_pContact->GetFixtureB()->GetBody()->GetUserData());

			bool l_bIsSensorColliderA = l_pColliderA->m_ColliderData.m_bIsSensor;
			bool l_bIsSensorColliderB = l_pColliderB->m_ColliderData.m_bIsSensor;

			if (l_bIsSensorColliderA && l_bIsSensorColliderB)
			{
				return;
			}
			manageCollisionContactStart(l_pColliderA, l_pColliderB);
			manageCollisionContactStart(l_pColliderB, l_pColliderA);
		}

		void Collider2D::EndContact(b2Contact* a_pContact)
		{
			Collider2D* l_pColliderA = static_cast<Collider2D*>(a_pContact->GetFixtureA()->GetBody()->GetUserData());
			Collider2D* l_pColliderB = static_cast<Collider2D*>(a_pContact->GetFixtureB()->GetBody()->GetUserData());

			bool l_bIsSensorColliderA = l_pColliderA->m_ColliderData.m_bIsSensor;
			bool l_bIsSensorColliderB = l_pColliderB->m_ColliderData.m_bIsSensor;

			if (l_bIsSensorColliderA && l_bIsSensorColliderB)
			{
				return;
			}

			manageCollisionContactEnd(l_pColliderA, l_pColliderB);
			manageCollisionContactEnd(l_pColliderB, l_pColliderA);
		}

		void Collider2D::callContactInSiblingComponents(void(IComponent::* FUNC_CONTACT)(Collider2D*), Collider2D* a_pOtherCollider)
		{
			const std::vector<IComponent*> l_vectComponents = m_GameObject.getAllComponents();

			for (auto l_Component = l_vectComponents.begin();
				l_Component != l_vectComponents.end(); l_Component++)
			{
				((*l_Component)->*FUNC_CONTACT)(a_pOtherCollider);
			}
		}

		void Collider2D::manageCollisionContactStart(Collider2D* a_pColliderA, Collider2D* a_pColliderB)
		{
			if (a_pColliderA->m_ColliderData.m_bIsSensor)
			{
				std::cout << "TRIGGER ENTER " << a_pColliderA->m_GameObject.getName() << "\n";
				a_pColliderA->callContactInSiblingComponents(&IComponent::onTriggerEnter2D, a_pColliderB);
			}
			else
			{
				if (!a_pColliderB->m_ColliderData.m_bIsSensor)
				{
					a_pColliderA->callContactInSiblingComponents(&IComponent::onCollisionEnter2D, a_pColliderB);
				}
			}
		}

		void Collider2D::manageCollisionContactEnd(Collider2D* a_pColliderA, Collider2D* a_pColliderB)
		{
			if (a_pColliderA->m_ColliderData.m_bIsSensor)
			{
				std::cout << "TRIGGER EXIT " << a_pColliderA->m_GameObject.getName() << "\n";
				a_pColliderA->callContactInSiblingComponents(&IComponent::onTriggerExit2D, a_pColliderB);
			}
			else
			{
				if (!a_pColliderB->m_ColliderData.m_bIsSensor)
				{
					a_pColliderA->callContactInSiblingComponents(&IComponent::onCollisionExit2D, a_pColliderB);
				}
			}
		}
	}
}