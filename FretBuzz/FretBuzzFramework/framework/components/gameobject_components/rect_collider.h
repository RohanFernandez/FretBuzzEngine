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
			RectCollider(GameObject& a_GameObject, glm::vec2 a_v2Dimensions, PhysicsEngine::PHYSICS_BODY_TYPE a_PhysicsBodyType = PhysicsEngine::PHYSICS_BODY_TYPE::STATIC
				, bool a_bIsFixedRotation = true);

			ns_graphics::LineData m_arrRectLineBorders[4];
			ns_graphics::Shader* m_pDefaultLineShader = nullptr;

		protected:
			virtual ~RectCollider();
			PhysicsEngine::PHYSICS_BODY_TYPE m_PhysicsBodyType = PhysicsEngine::PHYSICS_BODY_TYPE::STATIC;
			
			bool m_bIsFixedRotation = true;
			glm::vec2 m_v2Dimensions;
			b2Body* m_pBody = nullptr;
			b2Fixture* m_pFixture = nullptr;

			virtual void onEnable() override;
			virtual void onDisable() override;

		public:
			static RectCollider* addToGameObject(GameObject& a_GameObject, glm::vec2 a_v2Dimensions,
				PhysicsEngine::PHYSICS_BODY_TYPE a_PhysicsBodyType = PhysicsEngine::PHYSICS_BODY_TYPE::STATIC, bool a_bIsFixedRotation = true);

			void applyForce(b2Vec2 a_v2ForceDirection);
			void applyImpulse(b2Vec2 a_v2ImpulseDirection);

			void setLinearVelocity(b2Vec2 a_v2VelocityDirection);

			virtual void update(float a_fDeltaTime) override;
			virtual void debugRender(const glm::mat4& a_mat4Transformation, const ns_system::Viewport& a_Camera) override;
		};
	}
}