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

		public:
			PhysicsEngine(b2Vec2 a_v2Gravity);
			~PhysicsEngine();
		};
	}
}