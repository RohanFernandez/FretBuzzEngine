#pragma once

#include "window.h"
#include "timer/timerFPS.h"

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

		public:
			MasterRenderer(int a_iWidth, int a_iHeight, std::string a_strWindowName);
			~MasterRenderer();

			GLFWwindow* getGLFWWindow() const;
			bool isWindowClosed() const;

			float render(Game& m_Game);

		};
	}
}