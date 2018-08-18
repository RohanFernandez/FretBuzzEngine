#pragma once

#include "CharacterTest.h"
#include "../system/resource_manager.h"

namespace ns_fretBuzz
{

		CharacterTest::CharacterTest() 
			: ns_system::GameObject("character_test")
		{
			m_pAudSrc = &addComponent<ns_system::AudioSource>(ns_system::AudioSource("breakout"));

			m_pShader = ns_system::ResourceManager::getResource<ns_graphics::Shader>("tShader");
			m_pTexture = ns_system::ResourceManager::getResource<ns_graphics::Texture>("darksider");

			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_IBO);

			glBindVertexArray(m_VAO);

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)((sizeof(GLfloat) * 3)));
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

			glBindVertexArray(0);
		}

		void CharacterTest::update(float a_fDeltaTime)
		{
			if (ns_system::Input::IsKeyDown(GLFW_KEY_G))
			{
				m_pAudSrc->play();
			}

			if (ns_system::Input::IsKeyDown(GLFW_KEY_H))
			{
				m_pAudSrc->restart();
			}

			if (ns_system::Input::IsKeyDown(GLFW_KEY_J))
			{
				m_pAudSrc->stop();
			}

			if (ns_system::Input::IsKeyDown(GLFW_KEY_K))
			{
				m_pAudSrc->pause();

				ns_system::GameObject::update(a_fDeltaTime);
			}
		};

		void CharacterTest::render(const ns_system::Camera& a_Camera)
		{
			m_pShader->bind();

			m_pShader->setUniforMat4fv("unifProjection", a_Camera.getProjectionMatrix());
			m_pShader->setUniforMat4fv("unifView", a_Camera.getViewMatrix());

			glm::mat4 l_mat4SpriteModel = glm::mat4(1.0f);
			l_mat4SpriteModel = glm::translate(l_mat4SpriteModel, { 0.0f, 0.0f, 0.0f });
			l_mat4SpriteModel = glm::scale(l_mat4SpriteModel, { 600.0f, 400.0f, 0.0f });

			m_pShader->setUniforMat4fv("unifModel", (l_mat4SpriteModel));

			ns_system::Window::CheckForErrors();

			glActiveTexture(GL_TEXTURE0);
			m_pTexture->bind();

			m_pShader->setUniform1i("textureSampler", 0);

			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			GameObject::render(a_Camera);
		};
	}