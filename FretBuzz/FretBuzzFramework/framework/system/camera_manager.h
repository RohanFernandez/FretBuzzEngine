#pragma once
#include "../components/gameobject_components/camera.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class CameraManager
		{
		private:
			static CameraManager* s_pInstance;

			CameraManager();
			~CameraManager();

		public:
			static CameraManager* initialize();
			void destroy();
			static const CameraManager* get();
		};
	}
}