#include <fretbuzz_pch.h>
#include "mesh_renderer.h"
#include "system/game_object.h"
#include "graphics/shader_manager.h"

namespace ns_fretBuzz
{
	MeshRenderer::MeshRenderer(GameObject* a_GameObject, Mesh& a_Mesh)
		: IComponent(COMPONENT_TYPE::MESH_RENDERER, a_GameObject),
		IRenderer(),
		m_pMesh{ &a_Mesh }
	{
		m_Material.setShader(*ShaderManager::getShaderOfType(Shader::PHONG));
		m_Material.m_MaterialData.m_pTexDiffuse = m_pMesh->getTextureOfType(Mesh::MeshTexture::DIFFUSE);
		m_Material.m_MaterialData.m_pTexSpecular = m_pMesh->getTextureOfType(Mesh::MeshTexture::SPECULAR);
		setup();
	}

	MeshRenderer::~MeshRenderer()
	{
		
	}

	Mesh& MeshRenderer::getMesh()
	{
		return *m_pMesh;
	}

	void MeshRenderer::setup()
	{
		m_iVertBufferSize = (unsigned int)(m_pMesh->m_vectVertices.size() * sizeof(Mesh::Vertex));
		m_iTotalIndices = (unsigned int)m_pMesh->m_vectIndices.size();
		m_iIndexBufferSize = (unsigned int)(m_iTotalIndices * sizeof(unsigned int));

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_IBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_iVertBufferSize, &m_pMesh->m_vectVertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iIndexBufferSize, &m_pMesh->m_vectIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (const void*)offsetof(Mesh::Vertex, m_v3Position));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (const void*)offsetof(Mesh::Vertex, m_v3Normal));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (const void*)offsetof(Mesh::Vertex, m_v2TexCoords));

		glBindVertexArray(0);
	}

	void MeshRenderer::render(const glm::mat4& a_mat4Transformation, const Camera& a_Camera)
	{
		if (m_pMesh == nullptr)
		{
			return;
		}

		const glm::mat4 l_mat4RenderTransformation = a_Camera.getProjectionMatrix() * a_Camera.getViewMatrix() * m_GameObject.m_Transform.getTransformationMatrix();
		glm::mat4 l_m4Model = m_GameObject.m_Transform.getModelMatrix();

		m_Material.bind(a_Camera);
		m_Material.getShader()->setUniforMat4fv("u_m4Model", l_m4Model);
		m_Material.getShader()->setUniforMat4fv("u_m4transformation", l_mat4RenderTransformation);
		m_Material.getShader()->setUniforMat3fv("u_m3NormalMatrix", glm::mat3(glm::transpose(glm::inverse(l_m4Model))));

		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_iTotalIndices, GL_UNSIGNED_INT, NULL);

		/*unsigned int l_iDiffuseTexIndex = 1;
		unsigned int l_iSpecularTexIndex = 1;
		for (unsigned int l_iTexIndex = 0; l_iTexIndex < m_pMesh->m_vectTextures.size(); l_iTexIndex++)
		{
			glActiveTexture(GL_TEXTURE0 + l_iTexIndex);
				
			std::string number;
			std::string name = m_pMesh->m_vectTextures[l_iTexIndex].m_strType;
			if (name == "texture_diffuse")
				number = std::to_string(l_iDiffuseTexIndex++);
			else if (name == "texture_specular")
				number = std::to_string(l_iSpecularTexIndex++);

			m_pShader->setUniform1f(("material." + name + number).c_str(), l_iTexIndex);
			glBindTexture(GL_TEXTURE_2D, m_pMesh->m_vectTextures[l_iTexIndex].m_iTexID);
		}
		glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(m_pMesh->getVAO());
		glDrawElements(GL_TRIANGLES, m_pMesh->getIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);*/
	}
}
