#pragma once

#include "window.h"
#include "components/viewport.h"
#include "graphics/batch_renderer_manager.h"
#include "graphics/light_manager.h"
#include "graphics/shader_manager.h"
#include "graphics/post_process_manager.h"
#include "system/editor/editor_inspector.h"

namespace FRETBUZZ
{
	class SceneManager;

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

	public:

		static MasterRenderer* initialize(Window& a_Window);
		void destroy();
		static const MasterRenderer* get();

		void render(SceneManager& a_SceneManager, float a_fDeltaTime);

		void close() const;
	};
}