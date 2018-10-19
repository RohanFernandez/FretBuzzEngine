#pragma once
#include "mesh.h"
#include <glew.h>
#include <cstdlib>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Mesh::Mesh(std::vector<Vertex> a_vectVertices, std::vector<unsigned int> a_vectIndices,
			std::vector<MeshTexture> a_vectTextures)
			: m_vectVertices{ a_vectVertices },
			m_vectIndices{ a_vectIndices },
			m_vectTextures{ a_vectTextures }
		{
		}

		Mesh::~Mesh()
		{
		}

		Texture* Mesh::getTextureOfType(Mesh::MeshTexture::TYPE a_TextureType)
		{
			int l_iTexCount = m_vectTextures.size();
			for (int l_iTexIndex = 0; l_iTexIndex < l_iTexCount; l_iTexIndex++)
			{
				if (m_vectTextures[l_iTexIndex].m_Type == a_TextureType)
				{
					return m_vectTextures[l_iTexIndex].m_pTexture;
				}
			}
			return nullptr;
		}
	}
}