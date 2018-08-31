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

		public:
			PhysicsEngine();
			~PhysicsEngine();
		};
	}
}