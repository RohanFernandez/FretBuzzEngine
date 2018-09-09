#pragma once
#include "../../system/component.h"
#include "../../system/core/physics_engine.h"
#include "../../graphics/line_batch_renderer.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class GameObject;
		class RectCollider : public IComponent
		{
		private:
			RectCollider(GameObject& a_GameObject, glm::vec2 a_v2Dimensions, bool a_bIsStatic = true, bool a_bIsFixedRotation = true);
			virtual ~RectCollider();

			ns_graphics::LineData m_arrRectLineBorders[4];
			ns_graphics::Shader* m_pDefaultLineShader = nullptr;

		protected:
			bool m_bIsStatic = true;
			bool m_bIsFixedRotation = true;
			glm::vec2 m_v2Dimensions;
			b2Body* m_pBody = nullptr;
			b2Fixture* m_pFixture = nullptr;

		public:
			static RectCollider* addToGameObject(GameObject& a_GameObject, glm::vec2 a_v2Dimensions, bool a_bIsStatic = true, bool a_bIsFixedRotation = true);

			void applyForce(b2Vec2 a_v2ForceDirection);
			void applyImpulse(b2Vec2 a_v2ImpulseDirection);

			void setLinearVelocity(b2Vec2 a_v2VelocityDirection);

			virtual void update(float a_fDeltaTime) override;
			virtual void debugRender(const glm::mat4& a_mat4Transformation, const ns_system::Camera& a_Camera) override;
		};
	}
}