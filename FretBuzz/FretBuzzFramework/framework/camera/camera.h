#pragma once
#include "../components/math.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Camera
		{
		private:
			glm::vec3 a_v3Pos;
			glm::mat4 a_mat4Projection;

		public:
			Camera();
			virtual ~Camera() = 0;
		};
	}
}