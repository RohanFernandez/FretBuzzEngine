#pragma once
#include "master_renderer.h"
#include "../game.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//singleton instance
		MasterRenderer* MasterRenderer::s_pInstance = nullptr;

		MasterRenderer::MasterRenderer(int a_iWidth, int a_iHeight, std::string a_strWindowName, bool a_bLogFPS)
		{
			if (s_pInstance != nullptr)
			{
				return;
			}
			s_pInstance = this;

			m_pWindow = new Window(a_iWidth, a_iHeight, a_strWindowName);
			m_pSpriteBatchRenderer = new ns_graphics::SpriteBatchRenderer(10);
			m_pMainCamera = new OrthographicCamera{ glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f,M_PI,0.0f }, glm::vec3{ 1.0f,1.0f,1.0f }, -(float)m_pWindow->getWidth() / 2.0f, (float)m_pWindow->getWidth() / 2.0f, -(float)ns_system::Window::getHeight() / 2.0f, (float)ns_system::Window::getHeight() / 2.0f, -1.0f, 1.0f };
			m_pTimer = new TimerFPS(a_bLogFPS);
		}

		MasterRenderer:: ~MasterRenderer()
		{
			if (s_pInstance != this)
			{
				return;
			}

			if (m_pSpriteBatchRenderer != nullptr)
			{
				delete m_pSpriteBatchRenderer;
				m_pSpriteBatchRenderer = nullptr;
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
			m_pSpriteBatchRenderer->begin();

			m_pMainCamera->updateViewMatrix();
			m_Game.renderFrame(*m_pMainCamera);

			m_pSpriteBatchRenderer->end();
			m_pSpriteBatchRenderer->flush();

			m_pWindow->update();
			m_pTimer->update();
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

		void MasterRenderer::closeWindow() const
		{
			m_pWindow->closeWindow();
		}
	}
}