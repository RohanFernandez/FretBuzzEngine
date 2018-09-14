#pragma once
#include <Box2D/Box2D.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class PhysicsEngine
		{
		private:
			static PhysicsEngine* s_pInstance;

			b2World* m_pB2World = nullptr;

			int m_iVelocityIteration = 0;
			int m_iStepIteration = 0;

			PhysicsEngine(b2Vec2 a_v2Gravity, int a_iVelocityIteration, int a_iStepIteration);
			~PhysicsEngine();

		public:
			enum class PHYSICS_BODY_TYPE
			{
				STATIC,
				DYNAMIC,
				KINEMATIC
			};

			static PhysicsEngine* initialize(b2Vec2 a_v2Gravity, int a_iVelocityIteration, int a_iStepIteration);
			void destroy();
			static const PhysicsEngine* get();

			void update(float a_fDeltaTime);

			static b2World* getB2World();
		};
	}
}