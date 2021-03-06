#pragma once
#include "framework/system/game_object.h"
#include "framework/graphics/shader.h"
#include "framework/graphics/light_manager.h"
#include "light_cube.h"
#include "framework/graphics/material.h"

#include "framework/graphics/post_process_manager.h"
#include <resource_manager.h>

namespace ns_HMGame
{
	class test_cube: public FRETBUZZ::GameObject
	{
	public:

		float rot = 0.0f;

		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_IBO = 0;

		FRETBUZZ::Shader* m_pShader = nullptr;
		FRETBUZZ::Texture* m_pDiffuseTexture = nullptr;
		FRETBUZZ::Texture* m_pSpecularTexture = nullptr;

		FRETBUZZ::Material m_Material;
		FRETBUZZ::Material m_HighlighterMaterial;

		float m_vertices[288] = {
	-0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
	 0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
	 0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
	 0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
	-0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	-0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
	// Front face
	-0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
	 0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f, 0.0f, // bottom-right
	 0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f, // top-right
	 0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f, // top-right
	-0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, // top-left
	-0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
	// Left face
	-0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
	-0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
	-0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	-0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	-0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
	// Right face
	 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	 0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
	 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	 0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
	// Bottom face
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	 0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
	 0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	 0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	-0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	// Top face
	-0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	 0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	 0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
	 0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	-0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	-0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left      
		};

		FRETBUZZ::GameObject* m_pNanoSuit = nullptr;

		test_cube(FRETBUZZ::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_Position, FRETBUZZ::GameObject* a_pNanoSuit)
			: FRETBUZZ::GameObject(a_ParentGameObject, a_strName, a_Position, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
		{
			m_pNanoSuit = a_pNanoSuit;
			m_Material.setShader(*FRETBUZZ::ShaderManager::getShaderOfType(FRETBUZZ::Shader::PHONG));
			m_pDiffuseTexture = FRETBUZZ::ResourceManager::getResource<FRETBUZZ::Texture>("container_diffuse");
			m_pSpecularTexture = FRETBUZZ::ResourceManager::getResource<FRETBUZZ::Texture>("container_specular");

			m_Material.m_MaterialData.m_pTexDiffuse = m_pDiffuseTexture;
			m_Material.m_MaterialData.m_pTexSpecular = m_pSpecularTexture;

			m_HighlighterMaterial.setShader(*FRETBUZZ::ShaderManager::getShaderOfType(FRETBUZZ::Shader::DEFAULT_3D));
			m_HighlighterMaterial.m_MaterialData.m_v4Albedo = { 0.0f, 1.0f, 0.0f, 1.0f };

			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(3 * sizeof(float)));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(6 * sizeof(float)));

			glBindVertexArray(0);
		}

		virtual void update(const float& a_fDeltaTime) override
		{
			//rot = rot + M_PI * a_fDeltaTime * 0.5f;
			//m_Transform.setLocalRotation({ rot, rot , rot });

			glm::vec3 l_v3Scale = m_pNanoSuit->m_Transform.getLocalScale();
			if (FRETBUZZ::Input::IsMouseBtnDown(GLFW_MOUSE_BUTTON_1))
			{
				m_pNanoSuit->m_Transform.setLocalScale({ l_v3Scale + l_v3Scale * a_fDeltaTime *2.0F });
			}
			else if (FRETBUZZ::Input::IsMouseBtnDown(GLFW_MOUSE_BUTTON_2))
			{
				m_pNanoSuit->m_Transform.setLocalScale({ l_v3Scale - l_v3Scale * a_fDeltaTime *2.0F });
			}


			if (FRETBUZZ::Input::IsKeyPutDown(GLFW_KEY_C))
			{
				FRETBUZZ::PostProcessManager::togglePostProcess(!FRETBUZZ::PostProcessManager::isPostProcessActive());
			}

			
			if (FRETBUZZ::Input::IsKeyPutDown(GLFW_KEY_R))
			{
				FRETBUZZ::PostProcessManager::setPostProcessType(FRETBUZZ::Material::EDGE_DETECT);
			}
			else if (FRETBUZZ::Input::IsKeyPutDown(GLFW_KEY_T))
			{
				FRETBUZZ::PostProcessManager::setPostProcessType(FRETBUZZ::Material::BLUR);
			}
			else if (FRETBUZZ::Input::IsKeyPutDown(GLFW_KEY_Y))
			{
				FRETBUZZ::PostProcessManager::setPostProcessType(FRETBUZZ::Material::SHARPEN);
			}

			GameObject::update(a_fDeltaTime);
		}

		virtual void render(const FRETBUZZ::Camera& a_Camera) override
		{
			//glStencilFunc(GL_EQUAL, 1, 0xFF);
			m_Material.bind(a_Camera);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glClear(GL_STENCIL_BUFFER_BIT);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);

			const glm::mat4 l_mat4RenderTransformation = a_Camera.getProjectionMatrix() * a_Camera.getViewMatrix() * m_pTransform->getTransformationMatrix();

			glm::mat4 l_m4Model = m_pTransform->getModelMatrix();
			m_Material.getShader()->setUniforMat4fv("u_m4Model", l_m4Model);
			m_Material.getShader()->setUniforMat4fv("u_m4transformation", l_mat4RenderTransformation);
			m_Material.getShader()->setUniforMat3fv("u_m3NormalMatrix", glm::mat3(glm::transpose(glm::inverse(l_m4Model))));

			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			m_HighlighterMaterial.bind(a_Camera);
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(GL_FALSE);
			glDisable(GL_DEPTH_TEST);

			l_m4Model = glm::mat4(1.0f);
			l_m4Model = glm::translate(l_m4Model, m_Transform.getWorldPosition());
			l_m4Model = glm::scale(l_m4Model, m_Transform.getLocalScale() * 1.01f);
			l_m4Model *= m_Transform.getRotationTransformation();
			const glm::mat4 l_mat4HighLightRenderTransformation = a_Camera.getProjectionMatrix() * a_Camera.getViewMatrix() * l_m4Model;
			m_Material.getShader()->setUniforMat4fv("u_m4transformation", l_mat4HighLightRenderTransformation);

			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			glStencilMask(GL_TRUE);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glEnable(GL_DEPTH_TEST);
			
			GameObject::render(a_Camera);
		}
	};
}