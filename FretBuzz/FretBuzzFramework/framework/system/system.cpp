#pragma once
#include "system.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		System* System::s_pInstance = nullptr;

		System::System()
		{

		}

		bool System::initialize()
		{
			s_pInstance = new System();
			s_pInstance->m_pWindow = new Window(800, 600, "FretBuzz");
			s_pInstance->m_pInput = new Input();

			return (s_pInstance->m_pWindow->isInitialized() &&
				s_pInstance->m_pInput->isInitialized());
		}

		System::~System()
		{
			if (m_pWindow != nullptr)
			{
				delete m_pWindow;
				m_pWindow = nullptr;
			}

			if (m_pInput != nullptr)
			{
				delete m_pInput;
				m_pInput = nullptr;
			}

			s_pInstance = nullptr;
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
			while (!l_Window.isWindowClosed())
			{
				l_Window.clear();



				l_Window.update();
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