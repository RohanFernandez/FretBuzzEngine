#pragma once
#include "renderer.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		IRenderer::IRenderer()
		{
			
		}

		IRenderer::~IRenderer()
		{
			if (m_VBO)
			{ 
				glDeleteBuffers(1, &m_VBO);
				m_VBO = 0;
			}
			if (m_IBO) 
			{ 
				glDeleteBuffers(1, &m_IBO); 
				m_IBO = 0;
			}

			if (m_VAO) 
			{
				glDeleteVertexArrays(1, &m_VAO); 
				m_VAO = 0;
			}
		}
	}
}