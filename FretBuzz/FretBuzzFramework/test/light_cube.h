#pragma once
#include "../framework/system/game_object.h"
#include "../framework/graphics/shader.h"
#include "../framework/graphics/texture.h"
#include "../framework/utils/math.h"

namespace ns_fretBuzz
{
	class light_cube : public ns_system::GameObject
	{
	public:

		float rot = 0.0f;

		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_IBO = 0;

		glm::vec4 m_v4LightColor = {1.0f, 1.0f, 1.0f, 1.0f};

		ns_graphics::Shader* m_pShader = nullptr;

		float m_vertices[108] = {
	  -0.5f, -0.5f, -0.5f,
	   0.5f, -0.5f, -0.5f,
	   0.5f,  0.5f, -0.5f,
	   0.5f,  0.5f, -0.5f,
	  -0.5f,  0.5f, -0.5f,
	  -0.5f, -0.5f, -0.5f,

	  -0.5f, -0.5f,  0.5f,
	   0.5f, -0.5f,  0.5f,
	   0.5f,  0.5f,  0.5f,
	   0.5f,  0.5f,  0.5f,
	  -0.5f,  0.5f,  0.5f,
	  -0.5f, -0.5f,  0.5f,

	  -0.5f,  0.5f,  0.5f,
	  -0.5f,  0.5f, -0.5f,
	  -0.5f, -0.5f, -0.5f,
	  -0.5f, -0.5f, -0.5f,
	  -0.5f, -0.5f,  0.5f,
	  -0.5f,  0.5f,  0.5f,

	   0.5f,  0.5f,  0.5f,
	   0.5f,  0.5f, -0.5f,
	   0.5f, -0.5f, -0.5f,
	   0.5f, -0.5f, -0.5f,
	   0.5f, -0.5f,  0.5f,
	   0.5f,  0.5f,  0.5f,

	  -0.5f, -0.5f, -0.5f,
	   0.5f, -0.5f, -0.5f,
	   0.5f, -0.5f,  0.5f,
	   0.5f, -0.5f,  0.5f,
	  -0.5f, -0.5f,  0.5f,
	  -0.5f, -0.5f, -0.5f,

	  -0.5f,  0.5f, -0.5f,
	   0.5f,  0.5f, -0.5f,
	   0.5f,  0.5f,  0.5f,
	   0.5f,  0.5f,  0.5f,
	  -0.5f,  0.5f,  0.5f,
	  -0.5f,  0.5f, -0.5f
		};

		light_cube(ns_system::GameObject& a_ParentGameObject, std::string a_strName)
			: ns_system::GameObject(a_ParentGameObject, a_strName, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
		{
			m_pShader = ns_system::ResourceManager::getResource<ns_graphics::Shader>("lightShader");
			//m_pTexture = ns_system::ResourceManager::getResource<ns_graphics::Texture>("container");

			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			//glEnableVertexAttribArray(1);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
			//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3 * sizeof(float)));

			glBindVertexArray(0);
		}

		virtual void update(float a_fDeltaTime) override
		{
			rot = rot + M_PI * a_fDeltaTime * 0.5f;
			m_Transform.setLocalRotation({ rot, rot , rot });

			glm::vec3 l_newPosition{0.0f, 2.0f, 0.0f};
			l_newPosition.x = glm::sin(glfwGetTime()) * 3.0f;
			l_newPosition.z = glm::cos(glfwGetTime()) * 3.0f;
			m_Transform.setWorldPosition(l_newPosition);

			GameObject::update(a_fDeltaTime);
		}

		glm::vec4 getLightColor() const
		{
			return m_v4LightColor;
		}

		glm::vec3 getLightPosition() const
		{
			return m_Transform.getWorldPosition();
		}

		virtual void render(const ns_graphics::Camera& a_Camera) override
		{
			m_pShader->bind();

			const glm::mat4 l_mat4RenderTransformation = a_Camera.getProjectionMatrix() * a_Camera.getViewMatrix() * m_pTransform->getTransformationMatrix();
			m_pShader->setUniforMat4fv("u_m4transformation", l_mat4RenderTransformation);
			m_pShader->setUniform4f("u_v4LghtColor", m_v4LightColor);

			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			GameObject::render(a_Camera);
		}
	};
}