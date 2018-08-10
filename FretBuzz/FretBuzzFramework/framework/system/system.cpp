#pragma once
#include "system.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		System* System::s_pInstance = nullptr;

		const int System::START_SCREEN_WIDTH = 800;;
		const int System::START_SCREEN_HEIGHT = 600;
		const std::string System::WINDOW_NAME = "FretBuzz";

		System::System()
		{
			m_pWindow = new Window(START_SCREEN_WIDTH, START_SCREEN_HEIGHT, WINDOW_NAME);
			m_pFPStimer = new TimerFPS(true);
			m_pUpdateManager = new UpdateManager();
			m_pGame = new Game();
		}

		bool System::initialize()
		{
			s_pInstance = new System();
			return s_pInstance->m_pWindow->isInitialized();
		}

		System::~System()
		{
			if (m_pWindow != nullptr)
			{
				delete m_pWindow;
				m_pWindow = nullptr;
			}

			if (m_pFPStimer != nullptr)
			{
				delete m_pFPStimer;
				m_pFPStimer = nullptr;
			}

			if (m_pGame != nullptr)
			{
				delete m_pGame;
				m_pGame = nullptr;
			}

			if (m_pUpdateManager != nullptr)
			{
				delete m_pUpdateManager;
				m_pUpdateManager = nullptr;
			}

			if (s_pInstance == this)
			{
				s_pInstance = nullptr;
			}
		}

		void System::Run()
		{
			if (s_pInstance != nullptr)
			{
				return;
			}

			if (!initialize())
			{
				destroy();
				return;
			}

			Window& l_Window = *(s_pInstance->m_pWindow);
			TimerFPS& l_FPSTimer = *(s_pInstance->m_pFPStimer);
			Game& l_Game = *(s_pInstance->m_pGame);
			UpdateManager& l_UpdateManager = *(s_pInstance->m_pUpdateManager);

			float l_fCurrentDeltaTime = 0.0f;

			while (!l_Window.isWindowClosed())
			{
				l_Window.clear();
				l_fCurrentDeltaTime = l_FPSTimer.getDeltaTime();

				l_UpdateManager.onUpdateFrame(l_fCurrentDeltaTime);
				l_UpdateManager.onUpdateLateFrame(l_fCurrentDeltaTime);

				l_Window.update();
				l_FPSTimer.update();
			}

			destroy();
		}

		void System::destroy()
		{
			if (s_pInstance != nullptr)
			{
				delete s_pInstance;
				s_pInstance = nullptr;
			}
		}
	}
}