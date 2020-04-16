#include <fretbuzz_pch.h>
#include <glew.h>
#include "post_process_manager.h"
#include "shader_manager.h"
#include "system/core/window.h"
#include <utils/Event/Delegate/delegate.h>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		PostProcessManager* PostProcessManager:: s_pInstance = nullptr;

		PostProcessManager* PostProcessManager::initialize(unsigned int a_iWidth, unsigned int a_iHeight, Material::POST_PROCESS_TYPE a_PostProcessType)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "PostProcessManager::initialize:: PostProcessManager already exists.\n";
				return nullptr;
			}
			s_pInstance = new PostProcessManager(a_iWidth, a_iHeight, a_PostProcessType);
			return s_pInstance;
		}

		void PostProcessManager::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}

		const PostProcessManager* PostProcessManager::get()
		{
			return s_pInstance;
		}

		PostProcessManager::PostProcessManager(unsigned int a_iWidth, unsigned int a_iHeight, Material::POST_PROCESS_TYPE a_PostProcessType)
			:m_DataTexture(a_iWidth, a_iHeight, nullptr, GL_RGB)
		{
			Delegate<Window::WINDOW_RESIZE_TYPE> l_Delegate;
			l_Delegate.Add<PostProcessManager, &PostProcessManager::windowResize>(this);
			Window::registerWindowResizeCallback(l_Delegate);

			glGenFramebuffers(1, &m_FBO);
			glGenRenderbuffers(1, &m_RBO);

			if (!isSetupFrameBufferSuccess(a_iWidth, a_iHeight))
			{
				std::cout << "PostProcessManager::PostProcessManager:: Failed to initialize framebuffer \n";
			}

			glGenBuffers(1, &m_ScreenQuadVBO);
			glGenVertexArrays(1, &m_ScreenQuadVAO);

			glBindVertexArray(m_ScreenQuadVAO);

			glBindBuffer(GL_ARRAY_BUFFER, m_ScreenQuadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(RENDER_QUAD_DATA), &RENDER_QUAD_DATA, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, SIZE_SINGLE_VERTEX_DATA, (const GLvoid*)(0));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, SIZE_SINGLE_VERTEX_DATA, (const GLvoid*)(2 * sizeof(GLfloat)));

			glBindVertexArray(0);

			m_Material.m_MaterialData.m_PostProcessType = a_PostProcessType;
			m_Material.setShader(*ShaderManager::getShaderOfType(Shader::SHADER_TYPE::PP_DEFAULT));
		}

		bool PostProcessManager::isSetupFrameBufferSuccess(unsigned int a_uiWidth, unsigned int a_uiHeight)
		{
			bind();
			m_DataTexture.resetTextureDimension(a_uiWidth, a_uiHeight);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_DataTexture.getID(), 0);

			glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, a_uiWidth, a_uiHeight);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
			unbind();
			
			return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
		}

		PostProcessManager::~PostProcessManager()
		{
			Delegate<Window::WINDOW_RESIZE_TYPE> l_Delegate;
			l_Delegate.Add<PostProcessManager, &PostProcessManager::windowResize>(this);
			Window::unregisterWindowResizeCallback(l_Delegate);

			if (m_FBO)
			{
				glDeleteFramebuffers(1, &m_FBO);
				m_FBO = 0;
			}

			if (m_RBO)
			{
				glDeleteRenderbuffers(1, &m_RBO);
				m_RBO = 0;
			}

			if (m_ScreenQuadVAO)
			{
				glDeleteVertexArrays(1, &m_ScreenQuadVAO);
				m_ScreenQuadVAO = 0;
			}

			if (m_ScreenQuadVBO)
			{
				glDeleteBuffers(1, &m_ScreenQuadVBO);
				m_ScreenQuadVBO = 0;
			}
		}

		void PostProcessManager::bind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		}

		void PostProcessManager::unbind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void PostProcessManager::begin() const
		{
			if (m_bIsPostProcessOn)
			{
				bind(); 
			}
			else
			{
				unbind();
			}
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		void PostProcessManager::draw(unsigned int a_uiFrameBufferID, const Camera& a_MainCamera) const
		{
			if (!m_bIsPostProcessOn)
			{
				return;
			}

			glBindFramebuffer(GL_FRAMEBUFFER, a_uiFrameBufferID);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			m_Material.bind(a_MainCamera);

			glBindVertexArray(m_ScreenQuadVAO);

			glActiveTexture(GL_TEXTURE0);
			m_DataTexture.bind();

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		void PostProcessManager::togglePostProcess(bool a_bIsPostProcessOn)
		{
			s_pInstance->m_bIsPostProcessOn = a_bIsPostProcessOn;
		}

		bool PostProcessManager::isPostProcessActive()
		{
			return s_pInstance->m_bIsPostProcessOn;
		}

		void PostProcessManager::windowResize(int a_iWidth, int a_iHeight)
		{
			if (!isSetupFrameBufferSuccess(Window::getWidth(), Window::getHeight()))
			{
				std::cout << "PostProcessManager::windowResize:: Failed to resize framebuffer. \n";
			}
		}

		void PostProcessManager::setPostProcessType(Material::POST_PROCESS_TYPE a_PostProcessType)
		{
			s_pInstance->m_Material.m_MaterialData.m_PostProcessType = a_PostProcessType;
		}
	}
}