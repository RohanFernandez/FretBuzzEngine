#pragma once

#include "line_batch_renderer.h"
#include <cstddef>
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		LineBatchRenderer* LineBatchRenderer::s_pInstance = nullptr;

		LineBatchRenderer::LineBatchRenderer(unsigned int a_iMaxLines, float a_fLineWidth)
			:
			IBatchRenderer(),
			MAX_LINES{ a_iMaxLines},
			m_fLineWidth{a_fLineWidth}
		{
			if (s_pInstance != nullptr)
			{
				return;
			}
			s_pInstance = this;

			m_iTotalIndices = MAX_LINES * INDICES_PER_LINE;

			m_iIndexBufferSize = m_iTotalIndices * SIZE_OF_SINGLE_INDEX;
			m_iVertBufferSize = MAX_LINES * sizeof(VertexData) * VERTICES_PER_LINE;

			glGenBuffers(1, &m_VBO);
			glGenVertexArrays(1, &m_VAO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, m_iVertBufferSize, nullptr, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(INDEX_VERTEX);
			glEnableVertexAttribArray(INDEX_COLOR);

			glVertexAttribPointer(INDEX_VERTEX, 4, GL_FLOAT, GL_FALSE, SIZE_OF_VERTEX_DATA, (const GLvoid*)(offsetof(VertexData, VertexData::m_v4Position)));
			glVertexAttribPointer(INDEX_COLOR, 4, GL_FLOAT, GL_FALSE, SIZE_OF_VERTEX_DATA, (const GLvoid*)(offsetof(VertexData, VertexData::m_v4Color)));

			m_pIndexBufferArray = new GLuint[m_iIndexBufferSize];

			for (int l_iIBOindex = 0; l_iIBOindex < m_iIndexBufferSize; l_iIBOindex++)
			{
				m_pIndexBufferArray[l_iIBOindex] = l_iIBOindex;
			}

			glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndexBufferSize, m_pIndexBufferArray, GL_STATIC_DRAW);

			glBindVertexArray(0);
		}

		LineBatchRenderer::~LineBatchRenderer()
		{
			if (s_pInstance != this)
			{
				return;
			}

			if (m_pIndexBufferArray != nullptr)
			{
				delete[] m_pIndexBufferArray;
				m_pIndexBufferArray = nullptr;
			}

			if (m_VBO) { glDeleteBuffers(1, &m_VBO); }
			if (m_IBO) { glDeleteBuffers(1, &m_IBO); }
			if (m_VAO) { glDeleteVertexArrays(1, &m_VAO); }

			s_pInstance = nullptr;
		}

		void LineBatchRenderer::submit(const LineData* a_pLine, const int a_iNumOfLines, const glm::mat4& a_mat4Transformation, Shader* a_pShader)
		{
			LineBatchRenderer& l_Instance = *s_pInstance;

			if (((l_Instance.m_iIndicesToDraw != 0) &&
				(l_Instance.m_pCurrentShader != nullptr) &&
				(l_Instance.m_pCurrentShader->getShaderId() != a_pShader->getShaderId()))
				|| (l_Instance.m_iLinesInBatch == l_Instance.MAX_LINES))
			{
				l_Instance.end();
				l_Instance.flush();
				l_Instance.begin();
			}

			l_Instance.m_pCurrentShader = a_pShader;

			VertexData*& l_pCurrentVertexData = l_Instance.m_pCurrentVertexData;
			for (int l_iLineIndex = 0; l_iLineIndex < a_iNumOfLines; l_iLineIndex++)
			{
				l_pCurrentVertexData->m_v4Position = a_mat4Transformation * a_pLine[l_iLineIndex].m_v4StartPosition;
				l_pCurrentVertexData->m_v4Color = a_pLine->m_v4StartColor;
				l_pCurrentVertexData++;

				l_pCurrentVertexData->m_v4Position = a_mat4Transformation * a_pLine[l_iLineIndex].m_v4EndPosition;
				l_pCurrentVertexData->m_v4Color = a_pLine->m_v4EndColor;
				l_pCurrentVertexData++;

				l_Instance.m_iLinesInBatch++;
				l_Instance.m_iIndicesToDraw += 2;
			}
		}

		void LineBatchRenderer::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, s_pInstance->m_VBO);
			s_pInstance->m_pCurrentVertexData = (VertexData*)(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		}

		void LineBatchRenderer::end()
		{
			glBindBuffer(GL_ARRAY_BUFFER, s_pInstance->m_VBO);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			s_pInstance->m_pCurrentVertexData = nullptr;
		}

		void LineBatchRenderer::flush()
		{
			LineBatchRenderer& l_Instance = *s_pInstance;
			if (l_Instance.m_iIndicesToDraw == 0) { return; }

			l_Instance.m_pCurrentShader->bind();
			glBindVertexArray(l_Instance.m_VAO);

			glLineWidth(m_fLineWidth);
			glDrawElements(GL_LINES, l_Instance.m_iIndicesToDraw, GL_UNSIGNED_INT, NULL);

			//std::cout << "SpriteBatchRenderer::flush:: Total sprites drawn in batch ::" << l_Instance.m_iSpritesInBatch <<"\n";

			l_Instance.m_iIndicesToDraw = 0;
			l_Instance.m_iLinesInBatch = 0;
		}
	}
}