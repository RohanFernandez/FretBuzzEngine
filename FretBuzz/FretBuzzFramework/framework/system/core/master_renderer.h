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
		class CameraManager;
		class Game;
		class ns_graphics::LightManager;
		class MasterRenderer
		{
		private:
			static MasterRenderer* s_pInstance;

			Window* m_pWindow = nullptr;
			TimerFPS* m_pTimer = nullptr;

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

			float render(Game& m_Game);

			void closeWindow() const;

			static void windowResizeCallback();
		};
	}
}