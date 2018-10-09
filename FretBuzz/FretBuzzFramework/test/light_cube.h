#pragma once
#include "../framework/system/game_object.h"
#include "../framework/graphics/shader.h"
#include "../framework/graphics/texture.h"
#include "../framework/utils/math.h"
#include "../framework/components/gameobject_components/light.h"

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
		ns_graphics::Light* m_pLight = nullptr;

		glm::vec3 m_v3LightPosition;

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

		light_cube(ns_system::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, ns_graphics::Light::LIGHT_TYPE a_LightType, float a_fIntensity = 1.0f)
			: ns_system::GameObject(a_ParentGameObject, a_strName, a_v3Position, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
		{
			m_pShader = ns_system::ResourceManager::getResource<ns_graphics::Shader>("lightShader");
			//m_pTexture = ns_system::ResourceManager::getResource<ns_graphics::Texture>("container");

			m_pLight = ns_graphics::Light::addToGameObject(*this, a_LightType);
			ns_graphics::Light::LightSource& l_LightSource = m_pLight->m_LightSource;

			l_LightSource.m_v4LightPosition = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			l_LightSource.m_v3LightDirection = m_Transform.getForward();
			l_LightSource.m_v3ConstLinQuad = { 1.0f, 0.09f, 0.032f };
			l_LightSource.m_v3AmbientColor = {0.2f, 0.2f, 0.2f};
			l_LightSource.m_v3Diffuse = { 0.7f, 0.7f, 0.7f };
			l_LightSource.m_v3Specular = { 1.0f, 1.0f, 1.0f };
			l_LightSource.m_fIntensity = a_fIntensity;

			m_v3LightPosition = a_v3Position;
			
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
			/*rot = rot + M_PI * a_fDeltaTime * 0.5f;
			m_Transform.setLocalRotation({ rot, rot , rot });

			glm::vec3 l_newPosition{ m_v3LightPosition };
			l_newPosition.x = glm::sin(glfwGetTime()) * 3.0f * m_v3LightPosition.x;
			l_newPosition.z = glm::cos(glfwGetTime()) * 3.0f * m_v3LightPosition.z;
			m_Transform.setWorldPosition(l_newPosition);*/

			if (ns_system::Input::IsKeyPutDown(GLFW_KEY_0))
			{
				m_pLight->m_LightSource.m_fIntensity -= 0.1f;
			}
			else if (ns_system::Input::IsKeyPutDown(GLFW_KEY_1))
			{
				m_pLight->m_LightSource.m_fIntensity += 0.1f;
			}

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
		#if 0
			{
				m_pShader->bind();

				const glm::mat4 l_mat4RenderTransformation = a_Camera.getProjectionMatrix() * a_Camera.getViewMatrix() * m_pTransform->getTransformationMatrix();
				m_pShader->setUniforMat4fv("u_m4transformation", l_mat4RenderTransformation);
				m_pShader->setUniform4f("u_v4LghtColor", m_v4LightColor);

				glBindVertexArray(m_VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		#endif

			GameObject::render(a_Camera);
		}
	};
}