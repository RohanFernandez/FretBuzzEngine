#pragma once

#include "window.h"
#include "../timer/timerFPS.h"
#include "../../components/viewport.h"
#include "../../graphics/batch_renderer_manager.h"
#include "../../graphics/light_manager.h"
#include <vector>

namespace ns_fretBuzz
{
	namespace ns_system 
	{
		class Game;
	}

	namespace ns_graphics
	{
		class CameraManager;
		class LightManager;
		class MasterRenderer
		{
		private:
			static MasterRenderer* s_pInstance;

			Window* m_pWindow = nullptr;
			ns_system::TimerFPS* m_pTimer = nullptr;

			CameraManager* m_pCameraManager = nullptr;
			ns_graphics::LightManager* m_pLightManager = nullptr;


			ns_graphics::BatchRendererManager* m_pBatchRendererManager = nullptr;

			MasterRenderer(int a_iWidth, int a_iHeight, std::string a_strWindowName, bool a_bLogFPS = false);
			~MasterRenderer();

		public:

			static MasterRenderer* initialize(int a_iWidth, int a_iHeight, std::string a_strWindowName, bool a_bLogFPS = false);
			void destroy();
			static const MasterRenderer* get();

			GLFWwindow* getGLFWWindow() const;
			bool isWindowClosed() const;

			float render(ns_system::Game& m_Game);

			void closeWindow() const;

			static void windowResizeCallback();
		};
	}
}