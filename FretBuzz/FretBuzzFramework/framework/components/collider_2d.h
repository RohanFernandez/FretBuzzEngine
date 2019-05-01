#pragma once
#include <system/component_2d.h>
#include <components/collider_data.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Collider2D : public IComponent2D, protected b2ContactListener
		{
		public:

			void applyForce(glm::vec2 a_v2ForceDirection);
			void setLinearVelocity(glm::vec2 a_v2VelocityDirection);
			void applyImpulse(glm::vec2 a_v2ForceDirection);

#pragma region GETTERS AND SETTERS

			void setSensor(bool a_bIsSensor);
			bool isSensor() const;
			void setMaskBits(std::vector<uint16> a_vectMaskBits);
			std::vector<uint16> getMaskBits() const;
			void setCategoryBits(std::vector<uint16> a_vectCategoryBits);
			std::vector<uint16> getCategoryBits() const;

			uint16 GetBitField(std::vector<uint16>& a_vectBits) const;

#pragma endregion GETTERS AND SETTERS

		protected:
			Collider2D(GameObject2D& a_GameObject2D, ColliderData& a_ColliderData);
			~Collider2D();

			ColliderData m_ColliderData;
			b2Body* m_pBody = nullptr;
			b2Fixture* m_pFixture = nullptr;

			virtual void onEnable() override;
			virtual void onDisable() override;
			void Update(float a_fDeltaTime);

			void onSiblingComponentAdded(IComponent* a_pComponent);
			void onSiblingComponentRemoved(IComponent* a_pComponent);

			virtual void BeginContact(b2Contact* a_pContact) override;
			virtual void EndContact(b2Contact* a_pContact) override;

			void callContactInSiblingComponents(void(IComponent::* FUNC_CONTACT)(Collider2D*), Collider2D* a_pOtherCollider);

		private:
			void manageCollisionContactStart(Collider2D* a_pColliderA, Collider2D* a_pColliderB);
			void manageCollisionContactEnd(Collider2D* a_pColliderA, Collider2D* a_pColliderB);
		};
	}
}