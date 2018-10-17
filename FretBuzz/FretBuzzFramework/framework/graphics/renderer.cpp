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
			if (m_VBO) { glDeleteBuffers(1, &m_VBO); }
			if (m_IBO) { glDeleteBuffers(1, &m_IBO); }
			if (m_VAO) { glDeleteVertexArrays(1, &m_VAO); }
		}
	}
}