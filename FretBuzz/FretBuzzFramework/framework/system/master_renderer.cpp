#include <fretbuzz_pch.h>
#include "master_renderer.h"
#include "graphics/line_batch_renderer.h"
#include "graphics/sprite_batch_renderer.h"
#include "system/camera_manager.h"
#include <scene_manager.h>
#include "system.h"

namespace ns_fretBuzz
{
		//singleton instance
		MasterRenderer* MasterRenderer::s_pInstance = nullptr;

		MasterRenderer* MasterRenderer::initialize(Window& a_Window)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "MasterRenderer::initialize:: Master Renderer already exists.\n";
				return nullptr;
			}
			s_pInstance = new MasterRenderer(a_Window);
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

		MasterRenderer::MasterRenderer(Window& a_Window)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_SCISSOR_TEST);

			glDepthMask(GL_TRUE);
			glDepthFunc(GL_LESS);

			m_pBatchRendererManager = BatchRendererManager::intialize();
			m_pCameraManager = CameraManager::initialize();
			m_pLightManager = LightManager::initialize();
			m_pShaderManager = ShaderManager::initialize();
			//m_pPostProcessManager = PostProcessManager::initialize(a_iWidth, a_iHeight, Material::EDGE_DETECT);

			//m_pPostProcessManager->togglePostProcess(false);
		}

		MasterRenderer:: ~MasterRenderer()
		{
			m_pBatchRendererManager->destroy();
			//m_pPostProcessManager->destroy();
			m_pCameraManager->destroy();
			m_pLightManager->destroy();
			m_pShaderManager->destroy();
		}

		void MasterRenderer::render(SceneManager& a_SceneManager, float a_fDeltaTime)
		{
			//Render Pass
			m_pCameraManager->updateViewMatrix();
			std::vector<Camera*>& l_vectCameras = m_pCameraManager->getCameras();
			size_t l_iCameraCount = l_vectCameras.size();
			for (size_t l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
			{
				if (l_vectCameras[l_iCameraIndex]->isActiveAndEnabled())
				{
					//a_PostProcessManager.begin();

					Camera& l_CurrentCamera = *l_vectCameras[l_iCameraIndex];
					Window::get()->setViewport(l_CurrentCamera.getViewport());
					glEnable(GL_SCISSOR_TEST);
					glm::vec4& l_v4CamClearColour = l_CurrentCamera.m_v4ClearColour;
					glClearColor(l_v4CamClearColour.r, l_v4CamClearColour.g, l_v4CamClearColour.b, l_v4CamClearColour.a);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
					
					m_pBatchRendererManager->beginBatches();
					a_SceneManager.renderActiveScenes(l_CurrentCamera);
					m_pBatchRendererManager->endAndflushBatches();
					//a_PostProcessManager.draw(0, l_CurrentCamera);
				}
			}

#if _DEBUG

			

			/*ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/
#endif
		}

		void MasterRenderer::close() const
		{
		}
}