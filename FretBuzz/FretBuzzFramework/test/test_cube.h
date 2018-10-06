#pragma once
#include "../framework/system/game_object.h"
#include "../framework/graphics/shader.h"
#include "../framework/utils/math.h"
#include "light_cube.h"

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

		light_cube* m_pLightCube = nullptr;
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

		test_cube(ns_system::GameObject& a_ParentGameObject, std::string a_strName)
			: ns_system::GameObject(a_ParentGameObject, a_strName, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
		{
			m_pShader = ns_system::ResourceManager::getResource<ns_graphics::Shader>("cube");
			m_pDiffuseTexture = ns_system::ResourceManager::getResource<ns_graphics::Texture>("container_diffuse");
			m_pSpecularTexture = ns_system::ResourceManager::getResource<ns_graphics::Texture>("container_specular");

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

		void setLight(light_cube* a_pLightCube)
		{
			m_pLightCube = a_pLightCube;
		}

		void setCamGameObject(GameObject* a_pCamGameObject)
		{
			m_pCamGameObject = a_pCamGameObject;
		}

		virtual void render(const ns_system::Camera& a_Camera) override
		{
			m_pShader->bind();

			const glm::mat4 l_mat4RenderTransformation = a_Camera.getProjectionMatrix() * a_Camera.getViewMatrix() * m_pTransform->getTransformationMatrix();

			glm::mat4 l_m4Model = m_pTransform->getModelMatrix();
			m_pShader->setUniforMat4fv("u_m4Model", l_m4Model);
			m_pShader->setUniforMat4fv("u_m4transformation", l_mat4RenderTransformation);
			m_pShader->setUniforMat3fv("u_m3NormalMatrix", glm::mat3(glm::transpose(glm::inverse(l_m4Model))));

			m_pShader->setUniform3f("u_v3CamPosition", m_pCamGameObject->m_Transform.getWorldPosition());

			glm::vec4 l_v4LightVector = { /*glm::vec3{1.0f, 0.0f, 0.0f}*/m_pLightCube->getLightPosition(), 1.0f };
			m_pShader->setUniform4f("u_Light.m_v4LightVector", l_v4LightVector);
			m_pShader->setUniform3f("u_Light.m_v3ConstLinQuad", { 1.0f, 0.09f, 0.032f });
			m_pShader->setUniform3f("u_Light.m_v3AmbientColor", {0.2f, 0.2f, 0.2f});
			m_pShader->setUniform3f("u_Light.m_v3Diffuse", { 0.7f, 0.7f, 0.7f });
			m_pShader->setUniform3f("u_Light.m_v3Specular", { 1.0f, 1.0f, 1.0f });

			m_pShader->setUniform1f("u_Material.m_fShininess", 32.0f);

			glActiveTexture(GL_TEXTURE0);
			m_pDiffuseTexture->bind();
			m_pShader->setUniform1i("u_Material.m_texDiffuse", 0);

			glActiveTexture(GL_TEXTURE1);
			m_pSpecularTexture->bind();
			m_pShader->setUniform1i("u_Material.m_texSpecular", 1);

			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			GameObject::render(a_Camera);
		}
	};
}