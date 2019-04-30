#pragma once
#include <system/component_2d.h>
#include <components/collider_data.h>
#include <components/collision_events_2d.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Collider2D : public IComponent2D
		{
		public:
			void applyForce(glm::vec2 a_v2ForceDirection);
			void setLinearVelocity(glm::vec2 a_v2VelocityDirection);
			void applyImpulse(glm::vec2 a_v2ForceDirection);

		protected:
			Collider2D(COMPONENT_TYPE a_ComponentType, GameObject2D& a_GameObject2D, ColliderData& a_ColliderData);
			~Collider2D();

			ColliderData m_ColliderData;
			b2Body* m_pBody = nullptr;
			b2Fixture* m_pFixture = nullptr;
			std::list<CollisionEvents2D*> m_lstRegisteredCollisionEvents = std::list<CollisionEvents2D*>(10);

			void registerColliderEvent(IComponent* a_pIComponent);
			void unregisterColliderEvent(IComponent* a_pIComponent);

			virtual void onEnable() override;
			virtual void onDisable() override;
			void Update(float a_fDeltaTime);

			void onSiblingComponentAdded(IComponent* a_pComponent);
			void onSiblingComponentRemoved(IComponent* a_pComponent);
		};
	}
}