#pragma once
#include <components/raycast_callback.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		enum class PHYSICS_BODY_TYPE
		{
			STATIC		= 0,
			KINEMATIC	= 1,
			DYNAMIC		= 2
		};

		class FRETBUZZ_API PhysicsEngine
		{
		private:
			static PhysicsEngine* s_pInstance;

			b2World* m_pB2World = nullptr;
			RaycastCallback m_RaycastCallback;

			int m_iVelocityIteration = 0;
			int m_iStepIteration = 0;

			float m_fTimePassedSinceLastStep = 0.0f;

			PhysicsEngine(b2Vec2 a_v2Gravity, int a_iVelocityIteration, int a_iStepIteration);
			~PhysicsEngine();

		public:
			static PhysicsEngine* initialize(b2Vec2 a_v2Gravity, int a_iVelocityIteration, int a_iStepIteration);
			void destroy();
			static const PhysicsEngine* get();

			static b2World* getB2World();

			void step(float a_fDeltaTime);

			static void Raycast(Collider2D*& a_pCollider2D, glm::vec2& a_v2Point1, glm::vec2& a_v2Point2);
		};
	}
}