#pragma once
#include "master_renderer.h"
#include "../game/game.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//singleton instance
		MasterRenderer* MasterRenderer::s_pInstance = nullptr;

		MasterRenderer::MasterRenderer(int a_iWidth, int a_iHeight, std::string a_strWindowName)
		{
			if (s_pInstance != nullptr)
			{
				return;
			}
			s_pInstance = this;

			m_pWindow = new Window(a_iWidth, a_iHeight, a_strWindowName);
			m_pMainCamera = new OrthographicCamera{ glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f,180.0f,0.0f }, glm::vec3{ 1.0f,1.0f,1.0f }, -(float)m_pWindow->getWidth() / 2.0f, (float)m_pWindow->getWidth() / 2.0f, -(float)ns_system::Window::getHeight() / 2.0f, (float)ns_system::Window::getHeight() / 2.0f, -1.0f, 1.0f };
			m_pTimer = new TimerFPS(true);
		}

		MasterRenderer:: ~MasterRenderer()
		{
			if (s_pInstance != this)
			{
				return;
			}
			if (m_pTimer != nullptr)
			{
				delete m_pTimer;
				m_pTimer = nullptr;
			}

			if (m_pMainCamera != nullptr)
			{
				delete m_pMainCamera;
				m_pMainCamera;
			}

			if (m_pWindow != nullptr)
			{
				delete m_pWindow;
				m_pWindow = nullptr;
			}

			s_pInstance = nullptr;
		}

		float MasterRenderer::render(Game& m_Game)
		{
			m_pWindow->clear();

			m_pMainCamera->updateViewMatrix();
			m_Game.renderFrame(*m_pMainCamera);

			m_pTimer->update();
			m_pWindow->update();
			return m_pTimer->getDeltaTime();
		}

		bool MasterRenderer::isWindowClosed() const
		{
			return m_pWindow->isWindowClosed();
		}

		GLFWwindow* MasterRenderer::getGLFWWindow() const
		{
			return m_pWindow->getGLFWWindow();
		}
	}
}