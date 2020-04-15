#include <fretbuzz_pch.h>
#include "master_renderer.h"
#include "graphics/line_batch_renderer.h"
#include "graphics/sprite_batch_renderer.h"
#include "system/camera_manager.h"
#include "../scene_manager.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "system.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		MasterRenderer* MasterRenderer::s_pInstance = nullptr;

		MasterRenderer* MasterRenderer::initialize(int a_iWidth, int a_iHeight, std::string a_strWindowName, bool a_bLogFPS)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "MasterRenderer::initialize:: Master Renderer already exists.\n";
				return nullptr;
			}
			s_pInstance = new MasterRenderer(a_iWidth, a_iHeight, a_strWindowName, a_bLogFPS);
			return s_pInstance;
		}

		void MasterRenderer::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;	
		}

		const MasterRenderer* MasterRenderer::get()
		{
			return s_pInstance;
		}

		MasterRenderer::MasterRenderer(int a_iWidth, int a_iHeight, std::string a_strWindowName, bool a_bLogFPS)
		{
			m_pWindow = Window::initialize(a_iWidth, a_iHeight, a_strWindowName);
			Window::registerWindowResizeCallback(windowResizeCallback);

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
			glEnable(GL_DEPTH_TEST);

			m_pBatchRendererManager = BatchRendererManager::intialize();
			m_pCameraManager = CameraManager::initialize();
			m_pLightManager = LightManager::initialize();
			m_pShaderManager = ShaderManager::initialize();
			m_pPostProcessManager = PostProcessManager::initialize(a_iWidth, a_iHeight, Material::EDGE_DETECT);

			m_pPostProcessManager->togglePostProcess(false);

			m_pTimer = new ns_system::TimerFPS(a_bLogFPS);

#if _IS_DEBUG
			ImGui::CreateContext();
			ImGui::StyleColorsDark();
			ImGui_ImplGlfw_InitForOpenGL(getGLFWWindow(), true);
			ImGui_ImplOpenGL3_Init();
#endif
		}

		MasterRenderer:: ~MasterRenderer()
		{
			m_pBatchRendererManager->destroy();

			if (m_pTimer != nullptr)
			{
				delete m_pTimer;
				m_pTimer = nullptr;
			}
			
			m_pPostProcessManager->destroy();
			m_pCameraManager->destroy();
			m_pLightManager->destroy();
			m_pShaderManager->destroy();

			Window::unregisterWindowResizeCallback(windowResizeCallback);
			m_pWindow->destroy();
		}

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		float MasterRenderer::render(ns_system::SceneManager& a_SceneManager)
		{
			m_pWindow->clear();

			m_pBatchRendererManager->beginBatches();

			m_pCameraManager->updateViewMatrix();
			m_pCameraManager->renderFrame(a_SceneManager, *m_pPostProcessManager);
			
			m_pBatchRendererManager->endAndflushBatches();

#if _IS_DEBUG

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			m_pInspector->render(m_pTimer->getFPS());

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

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
#if _IS_DEBUG
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
#endif

			m_pWindow->closeWindow();
		}

		void MasterRenderer::windowResizeCallback()
		{
			s_pInstance->m_pCameraManager->windowResize();
			s_pInstance->m_pPostProcessManager->windowResize();
		}

#if _IS_DEBUG
		void MasterRenderer::setInspector(ns_editor::Inspector* a_pInspector)
		{
			m_pInspector = a_pInspector;
		}
#endif
	}
}