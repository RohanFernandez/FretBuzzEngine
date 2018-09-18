#pragma once
#include "../utils/math.h"
#include <string>
#include <vector>

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
				glm::vec3 m_v3TexCoords;
			};

			struct Texture
			{
				unsigned int m_iTexID;
				std::string m_strType;
			};

			std::vector<Vertex> m_vectVertices;
			std::vector<unsigned int> m_vectIndices;
			std::vector<Texture> m_vectTextures;

			Mesh(std::vector<Vertex> a_vectVertices, std::vector<unsigned int> a_vectIndices,
				std::vector<Texture> a_vectTextures);
			~Mesh();

			unsigned int getVAO() const;
			unsigned int getVBO() const;
			unsigned int getIBO() const;

			unsigned int getIndexCount() const;

		private:
			unsigned int m_VAO;
			unsigned int m_VBO;
			unsigned int m_IBO;

			void setup();
		};
	}
}