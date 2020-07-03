#pragma once
#include "system/game_object.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "components/gameobject_components/light.h"
#include "graphics/shader_manager.h"
#include "graphics/material.h"
#include <input.h>

namespace ns_HMGame
{
	class light_cube : public ns_fretBuzz::GameObject
	{
	public:

		float rot = 0.0f;

		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_IBO = 0;

		glm::vec4 m_v4LightColor = {1.0f, 1.0f, 1.0f, 1.0f};

		ns_fretBuzz::Light* m_pLight = nullptr;

		glm::vec3 m_v3LightPosition;

		ns_fretBuzz::Material m_Material;

		float m_vertices[108] = {
	-0.5f, -0.5f, -0.5f,  // Bottom-left
	 0.5f,  0.5f, -0.5f,  // top-right
	 0.5f, -0.5f, -0.5f,  // bottom-right         
	 0.5f,  0.5f, -0.5f,  // top-right
	-0.5f, -0.5f, -0.5f,  // bottom-left
	-0.5f,  0.5f, -0.5f,  // top-left
	// Front face
	-0.5f, -0.5f,  0.5f, // bottom-left
	 0.5f, -0.5f,  0.5f, // bottom-right
	 0.5f,  0.5f,  0.5f, // top-right
	 0.5f,  0.5f,  0.5f, // top-right
	-0.5f,  0.5f,  0.5f, // top-left
	-0.5f, -0.5f,  0.5f, // bottom-left
	// Left face
	-0.5f,  0.5f,  0.5f,  // top-right
	-0.5f,  0.5f, -0.5f,  // top-left
	-0.5f, -0.5f, -0.5f,  // bottom-left
	-0.5f, -0.5f, -0.5f,  // bottom-left
	-0.5f, -0.5f,  0.5f,  // bottom-right
	-0.5f,  0.5f,  0.5f,  // top-right
	// Right face
	 0.5f,  0.5f,  0.5f,  // top-left
	 0.5f, -0.5f, -0.5f,  // bottom-right
	 0.5f,  0.5f, -0.5f,  // top-right         
	 0.5f, -0.5f, -0.5f,  // bottom-right
	 0.5f,  0.5f,  0.5f,  // top-left
	 0.5f, -0.5f,  0.5f,  // bottom-left     
	// Bottom face
	-0.5f, -0.5f, -0.5f,  // top-right
	 0.5f, -0.5f, -0.5f,  // top-left
	 0.5f, -0.5f,  0.5f,  // bottom-left
	 0.5f, -0.5f,  0.5f,  // bottom-left
	-0.5f, -0.5f,  0.5f,  // bottom-right
	-0.5f, -0.5f, -0.5f,  // top-right
	// Top face
	-0.5f,  0.5f, -0.5f,  // top-left
	 0.5f,  0.5f,  0.5f,  // bottom-right
	 0.5f,  0.5f, -0.5f,  // top-right     
	 0.5f,  0.5f,  0.5f,  // bottom-right
	-0.5f,  0.5f, -0.5f,  // top-left
	-0.5f,  0.5f,  0.5f  // bottom-left    
		};

		light_cube(ns_fretBuzz::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, ns_fretBuzz::Light::LIGHT_TYPE a_LightType, float a_fIntensity = 2.0f)
			: GameObject(a_ParentGameObject, a_strName, a_v3Position, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f })
		{
			m_Material.setShader(*ns_fretBuzz::ShaderManager::getShaderOfType(ns_fretBuzz::Shader::DEFAULT_3D));
			//m_pTexture = ResourceManager::getResource<Texture>("container");

			m_pLight = ns_fretBuzz::Light::addToGameObject(*this, a_LightType);
			ns_fretBuzz::Light::LightSource& l_LightSource = m_pLight->m_LightSource;

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

		virtual void update(const float& a_fDeltaTime) override
		{
			if (m_pLight->getType() == ns_fretBuzz::Light::LIGHT_TYPE::POINT)
			{
				rot = rot + (float)M_PI * a_fDeltaTime * 0.5f;
				m_Transform.setLocalRotation({ rot, rot , rot });

				glm::vec3 l_newPosition{ m_v3LightPosition };
				l_newPosition.x = (float)(glm::sin(glfwGetTime()) * 5.0f * m_v3LightPosition.x);
				l_newPosition.z = (float)(glm::cos(glfwGetTime()) * 5.0f * m_v3LightPosition.z);
				m_Transform.setWorldPosition(l_newPosition);
			}

			if (ns_fretBuzz::Input::IsKeyPutDown(GLFW_KEY_0))
			{
				m_pLight->m_LightSource.m_fIntensity -= 0.1f;
			}
			else if (ns_fretBuzz::Input::IsKeyPutDown(GLFW_KEY_1))
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

		virtual void render(const ns_fretBuzz::Camera& a_Camera) override
		{
		if (m_pLight->getType() != ns_fretBuzz::Light::LIGHT_TYPE::SPOT)
			{
				m_Material.m_MaterialData.m_v4Albedo = m_v4LightColor;
				m_Material.bind(a_Camera);

				const glm::mat4 l_mat4RenderTransformation = a_Camera.getProjectionMatrix() * a_Camera.getViewMatrix() * m_pTransform->getTransformationMatrix();
				m_Material.m_pShader->setUniforMat4fv("u_m4transformation", l_mat4RenderTransformation);
				
				glBindVertexArray(m_VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		

			GameObject::render(a_Camera);
		}
	};
}