#include <fretbuzz_pch.h>
#include "collider_2d.h"
#include <bitset>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		Collider2D::Collider2D(GameObject2D* a_GameObject2D, ColliderData& a_ColliderData)
			: IComponent2D(COMPONENT_TYPE::COLLIDER_2D, a_GameObject2D),
			m_ColliderData{ a_ColliderData }
		{
			
		};

		void Collider2D::setupCollisionData()
		{
			b2BodyDef l_bodyDef;
			l_bodyDef.bullet = m_ColliderData.m_bIsBullet;

			l_bodyDef.type = (b2BodyType)m_ColliderData.m_PhysicsBodyType;

			glm::vec2 l_Position = m_GameObject.m_Transform.getWorldPosition();
			l_bodyDef.position.Set(l_Position.x, l_Position.y);
			l_bodyDef.angle = glm::eulerAngles(m_GameObject.m_Transform.getLocalRotation()).z;
			l_bodyDef.fixedRotation = m_ColliderData.m_bIsFixedRotation;
			l_bodyDef.linearDamping = m_ColliderData.m_fLinearDamping;
			l_bodyDef.angularDamping = m_ColliderData.m_fAngularDamping;

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
			else if (m_ColliderData.m_ColliderShape == m_ColliderData.SHAPE_CIRCLE)
			{
				l_circleShape.m_p.Set(m_ColliderData.m_v2RelativePos.x, m_ColliderData.m_v2RelativePos.y);
				l_circleShape.m_radius = m_ColliderData.m_fRadius;
				l_pb2Shape = &l_circleShape;
			}

			b2FixtureDef l_fixtureDef;
			l_fixtureDef.isSensor = m_ColliderData.m_bIsSensor;
			l_fixtureDef.shape = l_pb2Shape;
			l_fixtureDef.filter.categoryBits = m_ColliderData.m_CategoryMask.getBitfield();
			l_fixtureDef.filter.maskBits = m_ColliderData.m_CollisionMask.getBitfield();
			l_fixtureDef.filter.groupIndex = m_ColliderData.m_iGroupIndex ;
			l_fixtureDef.density = m_ColliderData.m_fDensity;
			l_fixtureDef.friction = m_ColliderData.m_fFriction;
			m_pFixture = m_pBody->CreateFixture(&l_fixtureDef);

			PhysicsEngine::getB2World()->SetContactListener(this);
		}

		Collider2D::~Collider2D()
		{
			b2World* l_pb2World = PhysicsEngine::getB2World();
		}

		void Collider2D::lateUpdate(float a_fDeltaTime)
		{
			if (m_ColliderData.m_PhysicsBodyType == PHYSICS_BODY_TYPE::DYNAMIC)
			{
				//Set transform position from collider position.
				const b2Vec2& l_v2ColliderPosition = m_pBody->GetPosition();
				m_GameObject.m_Transform.setWorldPosition({ l_v2ColliderPosition.x, l_v2ColliderPosition.y, m_GameObject.m_Transform.getWorldPosition().z });

				//Set transform rotation from collider rotation if the collider's rotation is not fixed.
				if (!m_ColliderData.m_bIsFixedRotation)
				{
					glm::vec3 l_v3tTransformRotation = glm::eulerAngles(m_GameObject.m_Transform.getLocalRotation());
					m_GameObject.m_Transform.setLocalRotation({ l_v3tTransformRotation.x , l_v3tTransformRotation.y , m_pBody->GetAngle() });
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
			m_pBody->SetEnabled(true);
		}

		void Collider2D::onDisable()
		{
			IComponent2D::onDisable();
			m_pBody->SetEnabled(false);
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

		glm::vec2 Collider2D::getLinearVelocity()
		{
			b2Vec2 l_b2v2LinearVelocity = m_pBody->GetLinearVelocity();
			return glm::vec2{ l_b2v2LinearVelocity.x, l_b2v2LinearVelocity.y};
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

		float Collider2D::getAngularVelocity()
		{
			return m_pBody->GetAngularVelocity();
		}

		void Collider2D::setLinearDamping(float a_fLinearDamping)
		{
			m_pBody->SetLinearDamping(a_fLinearDamping);
		}

		float Collider2D::getLinearDamping()
		{
			return m_pBody->GetLinearDamping();
		}

		void Collider2D::setAngularDamping(float a_fAngularDamping)
		{
			m_pBody->SetAngularDamping(a_fAngularDamping);
		}

		float Collider2D::getAngularDamping()
		{
			return m_pBody->GetAngularDamping();
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

#pragma region COLLISION MASK

		void Collider2D::setCollisionMask(const LayerMask& a_CollisionMask)
		{
			m_ColliderData.m_CollisionMask = a_CollisionMask;
			updateFilterData();
		}

		const LayerMask& Collider2D::Collider2D::getCollisionMask() const
		{
			return m_ColliderData.m_CollisionMask;
		}

		bool Collider2D::removeCollisionLayer(const std::string& a_strLayerName)
		{
			if (m_ColliderData.m_CollisionMask.removeLayer(a_strLayerName))
			{
				updateFilterData();
				return true;
			}
			return false;
		}

		bool Collider2D::addCollisionLayer(const std::string& a_strLayerName)
		{
			if (m_ColliderData.m_CollisionMask.addLayer(a_strLayerName))
			{
				updateFilterData();
				return true;
			}
			return false;
		}

#pragma endregion COLLISION MASK

#pragma region CATEGORY MASK

		///Category Mask
		void Collider2D::setCategoryMask(const LayerMask& a_LayerMask)
		{
			m_ColliderData.m_CategoryMask  = a_LayerMask;
			updateFilterData();
		}

		const LayerMask& Collider2D::Collider2D::getCategoryMask() const
		{
			return m_ColliderData.m_CategoryMask;
		}

		bool Collider2D::removeCategoryLayer(const std::string& a_strLayerName)
		{
			if (m_ColliderData.m_CategoryMask.removeLayer(a_strLayerName))
			{
				updateFilterData();
				return true;
			}
			return false;
		}

		bool Collider2D::addCategoryLayer(const std::string& a_strLayerName)
		{
			if (m_ColliderData.m_CategoryMask.addLayer(a_strLayerName))
			{
				updateFilterData();
				return true;
			}
			return false;
		}

#pragma endregion CATEGORY MASK

		void Collider2D::updateFilterData()
		{
			b2Filter l_b2Filter;
			l_b2Filter.maskBits = m_ColliderData.m_CollisionMask.getBitfield();
			l_b2Filter.categoryBits = m_ColliderData.m_CategoryMask.getBitfield();
			l_b2Filter.groupIndex = m_ColliderData.m_iGroupIndex;
			m_pFixture->SetFilterData(l_b2Filter);
		}

#pragma endregion GETTERS AND SETTERS

		// Contacts i.e. TriggerEnter, TriggerExit, CollisionEnter, CollisionExit that occured during step
		// are collected and invoked after the step because Box2D is locked during and no Box2D component should be calculated during.
		void Collider2D::BeginContact(b2Contact* a_pContact)
		{
			Collider2DContactEvent l_ContactEvent;
			l_ContactEvent.m_ContactEvent = &Collider2D::ManageContacts;
			l_ContactEvent.m_pFuncTriggerCallback = &IComponent::onTriggerEnter2D;
			l_ContactEvent.m_pFuncCollisionCallback = &IComponent::onCollisionEnter2D;
			l_ContactEvent.m_pColliderA = (static_cast<Collider2D*>(a_pContact->GetFixtureA()->GetBody()->GetUserData()));
			l_ContactEvent.m_pColliderB = (static_cast<Collider2D*>(a_pContact->GetFixtureB()->GetBody()->GetUserData()));
			PhysicsEngine::AddContactEvent(l_ContactEvent);
		}

		// Contacts i.e. TriggerEnter, TriggerExit, CollisionEnter, CollisionExit that occured during step
		// are collected and invoked after the step because Box2D is locked during and no Box2D component should be calculated during.
		void Collider2D::EndContact(b2Contact* a_pContact)
		{
			Collider2DContactEvent l_ContactEvent;
			l_ContactEvent.m_ContactEvent = &Collider2D::ManageContacts;
			l_ContactEvent.m_pFuncTriggerCallback = &IComponent::onTriggerExit2D;
			l_ContactEvent.m_pFuncCollisionCallback = &IComponent::onCollisionExit2D;
			l_ContactEvent.m_pColliderA = (static_cast<Collider2D*>(a_pContact->GetFixtureA()->GetBody()->GetUserData()));
			l_ContactEvent.m_pColliderB = (static_cast<Collider2D*>(a_pContact->GetFixtureB()->GetBody()->GetUserData()));
			PhysicsEngine::AddContactEvent(l_ContactEvent);
		}

		void Collider2D::callContactInSiblingComponents(FUNC_CONTACT_EVENT a_pFuncContact, Collider2D* a_pOtherCollider)
		{
			auto l_vectComponents = m_GameObject.getAllComponents();
			for (auto l_Component = l_vectComponents.begin();
				l_Component != l_vectComponents.end(); l_Component++)
			{
				(*l_Component->*a_pFuncContact)(a_pOtherCollider);
			}
		}

		void Collider2D::ManageContacts(Collider2D* a_pColliderA, Collider2D* a_pColliderB, FUNC_CONTACT_EVENT a_pFuncCollision, FUNC_CONTACT_EVENT a_pFuncTrigger)
		{
			bool l_bIsSensorA = a_pColliderA->m_ColliderData.m_bIsSensor;
			bool l_bIsSensorB = a_pColliderB->m_ColliderData.m_bIsSensor;

			//Both bodies are sensors
			if (l_bIsSensorA && l_bIsSensorB)
			{
				a_pColliderA->callContactInSiblingComponents(a_pFuncTrigger, a_pColliderB);
				a_pColliderB->callContactInSiblingComponents(a_pFuncTrigger, a_pColliderA);
			}
			//Both bodies are not sensors
			else if (l_bIsSensorA == l_bIsSensorB)
			{
				a_pColliderA->callContactInSiblingComponents(a_pFuncCollision, a_pColliderB);
				a_pColliderB->callContactInSiblingComponents(a_pFuncCollision, a_pColliderA);
			}
			else if (l_bIsSensorA)
			{
				a_pColliderA->callContactInSiblingComponents(a_pFuncTrigger, a_pColliderB);
			}
			else
			{
				a_pColliderB->callContactInSiblingComponents(a_pFuncTrigger, a_pColliderA);
			}
		}
	}
}