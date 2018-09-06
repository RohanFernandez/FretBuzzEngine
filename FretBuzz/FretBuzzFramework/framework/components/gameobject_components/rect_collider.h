#pragma once
#include "../../system/component.h"
#include "../../system/core/physics_engine.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class GameObject;
		class RectCollider : public IComponent
		{
		private:
			static constexpr COMPONENT_TYPE s_COMPONENT_TYPE = COMPONENT_TYPE::RECT_COLLIDER;

			RectCollider(GameObject& a_GameObject, glm::vec2 a_v2Dimensions, bool a_bIsStatic = true, bool a_bIsFixedRotation = true);
			virtual ~RectCollider();

		protected:
			bool m_bIsStatic = true;
			bool m_bIsFixedRotation = true;
			glm::vec2 m_v2Dimensions;
			b2Body* m_pBody = nullptr;
			b2Fixture* m_pFixture = nullptr;

		public:
			static RectCollider* addToGameObject(GameObject& a_GameObject, glm::vec2 a_v2Dimensions, bool a_bIsStatic = true, bool a_bIsFixedRotation = true);

			virtual void update(float a_fDeltaTime) override;
		};
	}
}