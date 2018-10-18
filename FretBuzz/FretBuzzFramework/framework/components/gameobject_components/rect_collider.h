#pragma once
#include "../../system/component_2d.h"
#include "../../system/core/physics_engine.h"
#include "../../graphics/line_batch_renderer.h"


namespace ns_fretBuzz
{
	namespace ns_system
	{
		class GameObject2D;
		class RectCollider : public IComponent2D
			#ifdef _IS_DEBUG_RENDERING
				,public ns_graphics::IRenderer
			#endif
		{
		private:
			RectCollider(GameObject2D& a_GameObject, glm::vec2 v2Dimensions, PhysicsEngine::PHYSICS_BODY_TYPE a_PhysicsBodyType = PhysicsEngine::PHYSICS_BODY_TYPE::STATIC
				, bool a_bIsFixedRotation = true, bool a_bIsBullet = false);

			ns_graphics::LineData m_arrRectLineBorders[4];

		protected:
			virtual ~RectCollider();
			PhysicsEngine::PHYSICS_BODY_TYPE m_PhysicsBodyType = PhysicsEngine::PHYSICS_BODY_TYPE::STATIC;
			
			bool m_bIsFixedRotation = true;
			b2Body* m_pBody = nullptr;
			b2Fixture* m_pFixture = nullptr;

			virtual void onEnable() override;
			virtual void onDisable() override;

			glm::vec2 m_v2DimensionWH;

		public:
			static RectCollider* addToGameObject(GameObject2D& a_GameObject,
				PhysicsEngine::PHYSICS_BODY_TYPE a_PhysicsBodyType = PhysicsEngine::PHYSICS_BODY_TYPE::STATIC, bool a_bIsFixedRotation = true, bool a_bIsBullet = false);
			static RectCollider* addToGameObject(GameObject2D& a_GameObject, glm::vec2 a_v2DimensionWH,
				PhysicsEngine::PHYSICS_BODY_TYPE a_PhysicsBodyType = PhysicsEngine::PHYSICS_BODY_TYPE::STATIC, bool a_bIsFixedRotation = true, bool a_bIsBullet = false);


			void applyForce(b2Vec2 a_v2ForceDirection);
			void applyImpulse(b2Vec2 a_v2ImpulseDirection);

			void setLinearVelocity(b2Vec2 a_v2VelocityDirection);

			virtual void update(float a_fDeltaTime) override;
			virtual void debugRender(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera) override;
		};
	}
}