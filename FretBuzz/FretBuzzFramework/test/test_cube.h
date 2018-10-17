#pragma once
#include "../framework/system/game_object.h"
#include "../framework/graphics/shader.h"
#include "../framework/utils/math.h"
#include "../framework/graphics/light_manager.h"
#include "light_cube.h"
#include "../framework/graphics/material.h"

namespace ns_fretBuzz
{
	class test_cube: public ns_system::GameObject
	{
	public:

		float rot = 0.0f;

		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_IBO = 0;

		ns_graphics::Shader* m_pShader = nullptr;
		ns_graphics::Texture* m_pDiffuseTexture = nullptr;
		ns_graphics::Texture* m_pSpecularTexture = nullptr;

		ns_graphics::Material m_Material;

		GameObject* m_pCamGameObject = nullptr;

		float m_vertices[288] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	 0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	 1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,	 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,	 1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,	 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,	 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,	 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,	 1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	 1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	 1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	 0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	 0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	 1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	 0.0f, 1.0f
		};

		test_cube(ns_system::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_Position)
			: ns_system::GameObject(a_ParentGameObject, a_strName, a_Position, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
		{
			m_Material.setShader(*ns_graphics::ShaderManager::getShaderOfType(ns_graphics::Shader::PHONG));
			m_pDiffuseTexture = ns_system::ResourceManager::getResource<ns_graphics::Texture>("container_diffuse");
			m_pSpecularTexture = ns_system::ResourceManager::getResource<ns_graphics::Texture>("container_specular");

			m_Material.m_MaterialData.m_pTexDiffuse = m_pDiffuseTexture;
			m_Material.m_MaterialData.m_pTexSpecular = m_pSpecularTexture;

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

		virtual void update(float a_fDeltaTime) override
		{
			//rot = rot + M_PI * a_fDeltaTime * 0.5f;
			//m_Transform.setLocalRotation({ rot, rot , rot });

			GameObject::update(a_fDeltaTime);
		}

		void setCamGameObject(GameObject* a_pCamGameObject)
		{
			m_pCamGameObject = a_pCamGameObject;
		}

		virtual void render(const ns_graphics::Camera& a_Camera) override
		{
			const glm::mat4 l_mat4RenderTransformation = a_Camera.getProjectionMatrix() * a_Camera.getViewMatrix() * m_pTransform->getTransformationMatrix();
			m_Material.bind(a_Camera);

			glm::mat4 l_m4Model = m_pTransform->getModelMatrix();
			m_Material.getShader()->setUniforMat4fv("u_m4Model", l_m4Model);
			m_Material.getShader()->setUniforMat4fv("u_m4transformation", l_mat4RenderTransformation);
			m_Material.getShader()->setUniforMat3fv("u_m3NormalMatrix", glm::mat3(glm::transpose(glm::inverse(l_m4Model))));

			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			GameObject::render(a_Camera);
		}
	};
}