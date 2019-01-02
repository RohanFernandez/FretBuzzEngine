#pragma once
#include "sprite_batch_renderer.h"
#include <cstddef>
#include <iostream>
#include "material.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		SpriteBatchRenderer* SpriteBatchRenderer::s_pInstance = nullptr;

		SpriteBatchRenderer::SpriteBatchRenderer(unsigned int a_iMaxSprites)
			: 
			IBatchRenderer(),
			MAX_SPRITES{a_iMaxSprites}
		{
			m_iTotalIndices = MAX_SPRITES * INDICES_PER_SPRITE;

			m_iIndexBufferSize = m_iTotalIndices * SIZE_OF_SINGLE_INDEX;
			m_iVertBufferSize = MAX_SPRITES * sizeof(VertexData) * VERTICES_PER_SPRITE;

			glGenBuffers(1, &m_VBO);
			glGenVertexArrays(1, &m_VAO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, m_iVertBufferSize, nullptr, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(INDEX_VERTEX);
			glEnableVertexAttribArray(INDEX_COLOR);
			glEnableVertexAttribArray(INDEX_TEX_UV);
			glEnableVertexAttribArray(INDEX_TEX_ID);

			glVertexAttribPointer(INDEX_VERTEX, 4, GL_FLOAT, GL_FALSE, SIZE_OF_VERTEX_DATA, (const GLvoid*)(offsetof(VertexData, VertexData::m_v4Position)));
			glVertexAttribPointer(INDEX_COLOR, 4, GL_FLOAT, GL_FALSE, SIZE_OF_VERTEX_DATA, (const GLvoid*)(offsetof(VertexData, VertexData::m_v4Color)));
			glVertexAttribPointer(INDEX_TEX_UV, 2, GL_FLOAT, GL_FALSE, SIZE_OF_VERTEX_DATA, (const GLvoid*)(offsetof(VertexData, VertexData::m_v2UV)));
			glVertexAttribPointer(INDEX_TEX_ID, 1, GL_FLOAT, GL_FALSE, SIZE_OF_VERTEX_DATA, (const GLvoid*)(offsetof(VertexData, VertexData::m_fTextureID)));

			m_pIndexBufferArray = new GLuint[m_iIndexBufferSize];

			unsigned int l_iOffset = 0;
			for (int l_iIBOindex = 0; l_iIBOindex < m_iIndexBufferSize; l_iIBOindex += 6)
			{
				//First Triangle
				m_pIndexBufferArray[l_iIBOindex] = l_iOffset;
				m_pIndexBufferArray[l_iIBOindex + 1] = l_iOffset + 2;
				m_pIndexBufferArray[l_iIBOindex + 2] = l_iOffset + 1;

				//Second Triangle
				m_pIndexBufferArray[l_iIBOindex + 3] = l_iOffset;
				m_pIndexBufferArray[l_iIBOindex + 4] = l_iOffset + 3;
				m_pIndexBufferArray[l_iIBOindex + 5] = l_iOffset + 2;

				l_iOffset += 4;
			}

			glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndexBufferSize, m_pIndexBufferArray, GL_STATIC_DRAW);
			
			glBindVertexArray(0);
		}

		SpriteBatchRenderer::~SpriteBatchRenderer()
		{
		}

		SpriteBatchRenderer* SpriteBatchRenderer::initialize(unsigned int a_iMaxSprites)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "SpriteBatchRenderer::initialize:: SpriteBatchRenderer previously initialized.\n";
				return nullptr;
			}
			s_pInstance = new SpriteBatchRenderer(a_iMaxSprites);
			return s_pInstance;
		}

		void SpriteBatchRenderer::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}

		void SpriteBatchRenderer::submit(const Sprite& a_Sprite, const glm::mat4& a_mat4Transformation, Material& a_Material)
		{
			submit(a_Sprite.getVertPosition() , a_Sprite.getColor(), a_Sprite.getTexture(), a_Sprite.getTexCoords(),
				a_mat4Transformation, a_Material);
		}

		void SpriteBatchRenderer:: submit(const std::vector<glm::vec4>& a_vectPosition, const glm::vec4& l_v4Color, 
			const Texture* a_pTexture, const std::vector<glm::vec2>& a_vectv2TexCoords,
			const glm::mat4& a_mat4Transformation, Material& a_Material)
		{
			SpriteBatchRenderer& l_Instance = *s_pInstance;
			
			if (((l_Instance.m_iIndicesToDraw != 0) &&
				(l_Instance.m_pCurrentShader != nullptr) &&
				(l_Instance.m_pCurrentShader->getShaderId() != a_Material.getShader()->getShaderId()))
				 || (l_Instance.m_iSpritesInBatch == l_Instance.MAX_SPRITES))
			{
				l_Instance.end();
				l_Instance.flush();
				l_Instance.begin();
			}

			if (l_Instance.m_pCurrentShader != a_Material.getShader())
			{
				a_Material.getShader()->bind();
				a_Material.getShader()->setUniform1iv(Material::MaterialData::UNIFORM_TEXTURE_SAMPLER, Material::MaterialData::TOTAL_TEXTURE_SLOTS, Material::MaterialData::s_arrTextureIDArray);
			}

			l_Instance.m_pCurrentShader = a_Material.getShader();

			float l_fTextureSlot = 0.0f;

			const unsigned int l_iTexID = (a_pTexture == nullptr) ? 0 : a_pTexture->getID();

			if (l_iTexID > 0)
			{
				bool l_bIsTextureIDFound = false;
				int l_iTexIDCount = l_Instance.m_vectActiveTexIDs.size();
				for (int l_iCurrentTexID = 0; l_iCurrentTexID < l_iTexIDCount; l_iCurrentTexID++)
				{
					if (l_iTexID == l_Instance.m_vectActiveTexIDs[l_iCurrentTexID])
					{
						l_fTextureSlot = (float)(1 + l_iCurrentTexID);
						l_bIsTextureIDFound = true;
						break;
					}
				}

				if (!l_bIsTextureIDFound)
				{
					if (l_iTexIDCount == 32)
					{
						l_Instance.end();
						l_Instance.flush();
						l_Instance.begin();
						l_Instance.m_vectActiveTexIDs.clear();
					}
					l_Instance.m_vectActiveTexIDs.push_back(l_iTexID);
					l_fTextureSlot = (float)l_Instance.m_vectActiveTexIDs.size();
				}
			}

			l_Instance.m_iSpritesInBatch++;
			VertexData*& l_pCurrentVertexData = l_Instance.m_pCurrentVertexData;

			l_pCurrentVertexData->m_v4Position = a_mat4Transformation * a_vectPosition[0];
			l_pCurrentVertexData->m_v4Color = l_v4Color;
			l_pCurrentVertexData->m_fTextureID = l_fTextureSlot;
			l_pCurrentVertexData->m_v2UV = a_vectv2TexCoords[0];
			l_pCurrentVertexData++;

			l_pCurrentVertexData->m_v4Position = a_mat4Transformation * a_vectPosition[1];
			l_pCurrentVertexData->m_v4Color = l_v4Color;
			l_pCurrentVertexData->m_fTextureID = l_fTextureSlot;
			l_pCurrentVertexData->m_v2UV = a_vectv2TexCoords[1];
			l_pCurrentVertexData++;

			l_pCurrentVertexData->m_v4Position = a_mat4Transformation * a_vectPosition[2];
			l_pCurrentVertexData->m_v4Color = l_v4Color;
			l_pCurrentVertexData->m_fTextureID = l_fTextureSlot;
			l_pCurrentVertexData->m_v2UV = a_vectv2TexCoords[2];
			l_pCurrentVertexData++;

			l_Instance.m_pCurrentVertexData->m_v4Position = a_mat4Transformation * a_vectPosition[3];
			l_Instance.m_pCurrentVertexData->m_v4Color = l_v4Color;
			l_Instance.m_pCurrentVertexData->m_fTextureID = l_fTextureSlot;
			l_Instance.m_pCurrentVertexData->m_v2UV = a_vectv2TexCoords[3];
			l_Instance.m_pCurrentVertexData++;

			l_Instance.m_iIndicesToDraw += 6;
		}

		void SpriteBatchRenderer::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, s_pInstance->m_VBO);
			s_pInstance->m_pCurrentVertexData = (VertexData*)(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		}

		void SpriteBatchRenderer::end()
		{
			glBindBuffer(GL_ARRAY_BUFFER, s_pInstance->m_VBO);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			s_pInstance->m_pCurrentVertexData = nullptr;
		}

		void SpriteBatchRenderer::flush()
		{
			SpriteBatchRenderer& l_Instance = *s_pInstance;
			if (l_Instance.m_iIndicesToDraw == 0) { return; }

			int l_iCount = l_Instance.m_vectActiveTexIDs.size();
			for (int l_iTexindex = 0; l_iTexindex < l_iCount; l_iTexindex++)
			{
				glActiveTexture(GL_TEXTURE0 + l_iTexindex);
				glBindTexture(GL_TEXTURE_2D, l_Instance.m_vectActiveTexIDs[l_iTexindex]);
			}

			l_Instance.m_pCurrentShader->bind();
			glBindVertexArray(l_Instance.m_VAO);
			glDrawElements(GL_TRIANGLES, l_Instance.m_iIndicesToDraw, GL_UNSIGNED_INT, NULL);

			//std::cout << "SpriteBatchRenderer::flush:: Total sprites drawn in batch ::" << l_Instance.m_iSpritesInBatch <<"\n";

			l_Instance.m_iIndicesToDraw = 0;
			l_Instance.m_iSpritesInBatch = 0;
		}
	}
}