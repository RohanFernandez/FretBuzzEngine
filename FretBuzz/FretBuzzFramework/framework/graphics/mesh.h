#pragma once
#include "utils/math.h"
#include "texture.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Mesh
		{
		public:

			struct Vertex
			{
				glm::vec3 m_v3Position;
				glm::vec3 m_v3Normal;
				glm::vec2 m_v2TexCoords;
			};

			struct MeshTexture
			{
				enum TYPE
				{
					DIFFUSE,
					SPECULAR
				};

				Texture* m_pTexture = nullptr;
				TYPE m_Type;
			};

			std::vector<Vertex> m_vectVertices;
			std::vector<unsigned int> m_vectIndices;
			std::vector<MeshTexture> m_vectTextures;

			Mesh(std::vector<Vertex> a_vectVertices, std::vector<unsigned int> a_vectIndices,
				std::vector<MeshTexture> a_vectTextures);
			~Mesh();

			Texture* getTextureOfType(Mesh::MeshTexture::TYPE a_TextureType);
		};
	}
}