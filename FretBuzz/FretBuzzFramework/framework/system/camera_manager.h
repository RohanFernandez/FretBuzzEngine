#pragma once
#include "components/gameobject_components/camera.h"
#include "system/scene_manager.h"
#include "utils/resource_container.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class PostProcessManager;
		class FRETBUZZ_API CameraManager : ResourceContainer<std::vector<Camera*>>
		{
		private:
			static CameraManager* s_pInstance;

			CameraManager();
			~CameraManager();

		public:
			static CameraManager* initialize();
			void destroy();
			static const CameraManager* get();
			Camera& getMainCamera();

			void registerCamera(Camera* a_pCamera);
			static void s_registerCamera(Camera* a_pCamera);

			void unregisterCamera(Camera* a_pCamera);
			static void s_unregisterCamera(Camera* a_pCamera);

			void updateViewMatrix();
			void renderFrame(ns_system::SceneManager& a_SceneManager, const PostProcessManager& a_PostProcessManager);
			void windowResize();
		};
	}
}