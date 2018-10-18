#pragma once
#include "mesh_renderer.h"
#include "../../system/game_object.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		MeshRenderer::MeshRenderer(ns_system::GameObject& a_GameObject)
			: ns_system::IComponent(ns_system::COMPONENT_TYPE::MESH_RENDERER, a_GameObject),
			IRenderer()
		{
			
		}

		MeshRenderer::~MeshRenderer()
		{
		
		}

		MeshRenderer* MeshRenderer::addToGameObject(ns_system::GameObject& a_GameObject)
		{
			return IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::MESH_RENDERER, &a_GameObject) ?
				nullptr : new MeshRenderer(a_GameObject);
		}

		void MeshRenderer::setMesh(Mesh* a_pMesh)
		{
			m_pMesh = a_pMesh;
		}

		Mesh* MeshRenderer::getMesh()
		{
			return m_pMesh;
		}

		void MeshRenderer::render(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera)
		{
			if (m_pMesh == nullptr)
			{
				return;
			}

			unsigned int l_iDiffuseTexIndex = 1;
			unsigned int l_iSpecularTexIndex = 1;
			for (unsigned int l_iTexIndex = 0; l_iTexIndex < m_pMesh->m_vectTextures.size(); l_iTexIndex++)
			{
				glActiveTexture(GL_TEXTURE0 + l_iTexIndex);
				
				/*std::string number;
				std::string name = m_pMesh->m_vectTextures[l_iTexIndex].m_strType;
				if (name == "texture_diffuse")
					number = std::to_string(l_iDiffuseTexIndex++);
				else if (name == "texture_specular")
					number = std::to_string(l_iSpecularTexIndex++);*/

				//m_pShader->setUniform1f(("material." + name + number).c_str(), l_iTexIndex);
				//glBindTexture(GL_TEXTURE_2D, m_pMesh->m_vectTextures[l_iTexIndex].m_iTexID);
			}
			glActiveTexture(GL_TEXTURE0);

			glBindVertexArray(m_pMesh->getVAO());
			glDrawElements(GL_TRIANGLES, m_pMesh->getIndexCount(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
}
