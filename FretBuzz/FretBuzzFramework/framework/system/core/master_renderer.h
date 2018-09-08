#pragma once

#include "window.h"
#include "../timer/timerFPS.h"
#include "../../components/camera.h"
#include "../../graphics/batch_renderer.h"
#include <vector>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Game;
		class MasterRenderer
		{
		private:
			static MasterRenderer* s_pInstance;

			Window* m_pWindow = nullptr;
			TimerFPS* m_pTimer = nullptr;

			Camera* m_pMainCamera;

			std::vector<ns_graphics::BatchRenderer*> m_VectBatchRenderers;

		public:
			MasterRenderer(int a_iWidth, int a_iHeight, std::string a_strWindowName, bool a_bLogFPS = false);
			~MasterRenderer();

			GLFWwindow* getGLFWWindow() const;
			bool isWindowClosed() const;

			float render(Game& m_Game);

			void closeWindow() const;

			static void windowResizeCallback();
		};
	}
}