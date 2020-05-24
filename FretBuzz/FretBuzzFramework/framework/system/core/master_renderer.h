#pragma once

#include "window.h"
#include "components/viewport.h"
#include "graphics/batch_renderer_manager.h"
#include "graphics/light_manager.h"
#include "graphics/shader_manager.h"
#include "graphics/post_process_manager.h"
#include "system/editor/editor_inspector.h"

namespace ns_fretBuzz
{
	namespace ns_system 
	{
		class SceneManager;
	}

	namespace ns_graphics
	{
		class CameraManager;
		class LightManager;
		class ShaderManager;
		class  MasterRenderer
		{
		private:
			static MasterRenderer* s_pInstance;

			CameraManager* m_pCameraManager = nullptr;
			LightManager* m_pLightManager = nullptr;
			ShaderManager* m_pShaderManager = nullptr;

			PostProcessManager* m_pPostProcessManager = nullptr;

			BatchRendererManager* m_pBatchRendererManager = nullptr;

			MasterRenderer(Window& a_Window);
			~MasterRenderer();

#if _IS_DEBUG
			ns_editor::Inspector* m_pInspector = nullptr;
#endif

		public:

			static MasterRenderer* initialize(Window& a_Window);
			void destroy();
			static const MasterRenderer* get();

			void render(ns_system::SceneManager& a_SceneManager, float a_fDeltaTime);

			void closeWindow() const;

#if _IS_DEBUG
			void setInspector(ns_editor::Inspector* a_pInspector);
#endif
		};
	}
}