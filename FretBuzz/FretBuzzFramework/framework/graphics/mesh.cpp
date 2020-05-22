#include <fretbuzz_pch.h>
#include "mesh.h"
#include <GL/glew.h>

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
			size_t l_iTexCount = m_vectTextures.size();
			for (size_t l_iTexIndex = 0; l_iTexIndex < l_iTexCount; l_iTexIndex++)
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