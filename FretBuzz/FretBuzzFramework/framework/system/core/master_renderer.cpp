#pragma once
#include "master_renderer.h"
#include "../game.h"
#include "../../graphics/line_batch_renderer.h"
#include "../../graphics/sprite_batch_renderer.h"

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
			Window::registerWindowResizeCallback(windowResizeCallback);

			m_VectBatchRenderers.emplace_back(new ns_graphics::SpriteBatchRenderer(10));
			m_VectBatchRenderers.emplace_back(new ns_graphics::LineBatchRenderer(100, 10.0f));

			m_pMainCamera = new OrthographicCamera{ glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f,M_PI,0.0f }, glm::vec3{ 1.0f,1.0f,1.0f }, -(float)m_pWindow->getWidth() / 2.0f, (float)m_pWindow->getWidth() / 2.0f, -(float)m_pWindow->getHeight() / 2.0f, (float)m_pWindow->getHeight() / 2.0f, -1.0f, 1.0f };
			m_pTimer = new TimerFPS(a_bLogFPS);
		}

		MasterRenderer:: ~MasterRenderer()
		{
			if (s_pInstance != this)
			{
				return;
			}

			for (std::vector<ns_graphics::BatchRenderer*>::iterator l_Iterator = m_VectBatchRenderers.begin();
				l_Iterator != m_VectBatchRenderers.end();)
			{
				delete (*l_Iterator);
				l_Iterator = m_VectBatchRenderers.erase(l_Iterator);
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
				Window::unregisterWindowResizeCallback(windowResizeCallback);
				delete m_pWindow;
				m_pWindow = nullptr;
			}

			s_pInstance = nullptr;
		}

		float MasterRenderer::render(Game& m_Game)
		{
			m_pWindow->clear();

			int l_iBatchRendererCount = m_VectBatchRenderers.size();
			for (int l_iBatchRendererIndex = 0; l_iBatchRendererIndex < l_iBatchRendererCount; l_iBatchRendererIndex++)
			{
				m_VectBatchRenderers[l_iBatchRendererIndex]->begin();
			}

			m_pMainCamera->updateViewMatrix();
			m_Game.renderFrame(*m_pMainCamera);

			for (int l_iBatchRendererIndex = 0; l_iBatchRendererIndex < l_iBatchRendererCount; l_iBatchRendererIndex++)
			{
				m_VectBatchRenderers[l_iBatchRendererIndex]->end();
				m_VectBatchRenderers[l_iBatchRendererIndex]->flush();
			}

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

		void MasterRenderer::windowResizeCallback()
		{
			OrthographicCamera* l_pOrthoCamera = dynamic_cast<OrthographicCamera*>(s_pInstance->m_pMainCamera);
			if (l_pOrthoCamera != nullptr)
			{
				glm::vec2 l_v2NearFar = l_pOrthoCamera->getNearFar();
				l_pOrthoCamera->setProjectionMatrix(-(float)Window::getWidth() / 2.0f, (float)Window::getWidth() / 2.0f, -(float)ns_system::Window::getHeight() / 2.0f, (float)ns_system::Window::getHeight() / 2.0f, l_v2NearFar.x, l_v2NearFar.y);
			}

			PerspectiveCamera* l_pPerspectiveCamera = dynamic_cast<PerspectiveCamera*>(s_pInstance->m_pMainCamera);
			if (l_pPerspectiveCamera != nullptr)
			{
				glm::vec2 l_v2NearFar = l_pPerspectiveCamera->getNearFar();
				l_pPerspectiveCamera->setProjectionMatrix(l_pPerspectiveCamera->getFOV(), l_pPerspectiveCamera->getAspectRatio(), l_v2NearFar.x, l_v2NearFar.y);
			}
		}
	}
}