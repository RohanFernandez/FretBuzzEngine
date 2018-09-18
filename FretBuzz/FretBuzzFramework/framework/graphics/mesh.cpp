#pragma once
#include "mesh.h"
#include <glew.h>
#include <cstdlib>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Mesh::Mesh(std::vector<Vertex> a_vectVertices, std::vector<unsigned int> a_vectIndices,
			std::vector<Texture> a_vectTextures)
			: m_vectVertices{ a_vectVertices },
			m_vectIndices{ a_vectIndices },
			m_vectTextures{ a_vectTextures }
		{
			setup();
		}

		Mesh::~Mesh()
		{
			if (m_VBO) { glDeleteBuffers(1, &m_VBO); }
			if (m_IBO) { glDeleteBuffers(1, &m_IBO); }
			if (m_VAO) { glDeleteVertexArrays(1, &m_VAO); }
		}

		void Mesh::setup()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_IBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER ,m_VAO);

			glBufferData(GL_ARRAY_BUFFER, m_vectVertices.size() * sizeof(Vertex), &m_vectVertices[0], GL_STATIC_DRAW);

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vectIndices.size() * sizeof(unsigned int), &m_vectIndices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_v3Position));
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_v3Normal));
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_v3TexCoords));

			glBindVertexArray(0);
		}

		unsigned int Mesh::getVAO() const
		{
			return m_VAO;
		}

		unsigned int Mesh::getVBO() const
		{
			return m_VBO;
		}

		unsigned int Mesh::getIBO() const
		{
			return m_IBO;
		}

		unsigned int Mesh::getIndexCount() const
		{
			return m_vectIndices.size();
		}
	}
}