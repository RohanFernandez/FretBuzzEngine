#pragma once
#include "../framework/system/game_object.h"
#include "../framework/graphics/shader.h"
#include "../framework/utils/math.h"

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
		ns_graphics::Texture* m_pTexture = nullptr;

		float m_vertices[180] = {
	  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	   0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	   0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	   0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	   0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		test_cube(ns_system::GameObject& a_ParentGameObject, std::string a_strName)
			: ns_system::GameObject(a_ParentGameObject, a_strName, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
		{
			m_pShader = ns_system::ResourceManager::getResource<ns_graphics::Shader>("cube");
			m_pTexture = ns_system::ResourceManager::getResource<ns_graphics::Texture>("container");

			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3 * sizeof(float)));

			glBindVertexArray(0);
		}

		virtual void update(float a_fDeltaTime) override
		{
			rot = rot + M_PI * a_fDeltaTime * 0.5f;
			m_Transform.setLocalRotation({ rot, rot , rot });

			GameObject::update(a_fDeltaTime);
		}

		virtual void render(const ns_system::Camera& a_Camera) override
		{
			m_pShader->bind();
			m_pShader->setUniform1i("texSampler", 0);

			m_pTexture->bind();
			glActiveTexture(GL_TEXTURE0);


			const glm::mat4 l_mat4RenderTransformation = a_Camera.getProjectionMatrix() * a_Camera.getViewMatrix() * m_pTransform->getTransformationMatrix();

			glm::mat4 l_mat4{ 1.0f };
			l_mat4 = glm::translate(l_mat4, {2.0f, 0.0f, 0.0f});
			l_mat4 = glm::rotate(l_mat4, rot, { 1.0f, 0.0f, 0.0f });
			l_mat4 = glm::rotate(l_mat4, rot, { 0.0f, 1.0f, 0.0f });
			l_mat4 = glm::rotate(l_mat4, rot, { 0.0f, 0.0f, 1.0f });

			const glm::mat4 l_mat4RenderTransformation1 = a_Camera.getProjectionMatrix() * a_Camera.getViewMatrix() * l_mat4;

			m_pShader->setUniforMat4fv("u_m4transformation", l_mat4RenderTransformation);

			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			m_pShader->setUniforMat4fv("u_m4transformation", l_mat4RenderTransformation1);
			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			ns_system::Window::CheckForErrors();

			GameObject::render(a_Camera);
		}
	};
}