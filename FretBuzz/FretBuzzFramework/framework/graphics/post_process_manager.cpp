#pragma once
#include <glew.h>
#include <iostream>
#include "post_process_manager.h"
#include "shader_manager.h"

#include "../system/core/window.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		PostProcessManager* PostProcessManager:: s_pInstance = nullptr;

		PostProcessManager* PostProcessManager::initialize(unsigned int a_iWidth, unsigned int a_iHeight)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "PostProcessManager::initialize:: PostProcessManager already exists.\n";
				return nullptr;
			}
			s_pInstance = new PostProcessManager(a_iWidth, a_iHeight);
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

		PostProcessManager::PostProcessManager(unsigned int a_iWidth, unsigned int a_iHeight)
			:m_DataTexture(a_iWidth, a_iHeight, nullptr, GL_RGB)
		{
			glGenFramebuffers(1, &m_FBO);
			glGenRenderbuffers(1, &m_RBO);

			bind();
			m_DataTexture.bind();
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_DataTexture.getID(), 0);

			glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
			Window::CheckForErrors();
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, a_iWidth, a_iHeight);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			{
				std::cout << "PostProcess::PostProcess:: Failed to initialize framebuffer \n";
			}
			unbind();

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
			m_Material.setShader(*ShaderManager::getShaderOfType(Shader::SHADER_TYPE::PP_DEFAULT));
		}

		PostProcessManager::~PostProcessManager()
		{
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
			m_bIsPostProcessOn = a_bIsPostProcessOn;
		}

		bool PostProcessManager::isPostProcessActive() const
		{
			return m_bIsPostProcessOn;
		}
	}
}