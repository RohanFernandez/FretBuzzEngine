#pragma once

#include "CharacterTest.h"

namespace ns_fretBuzz
{

		CharacterTest::CharacterTest() 
			: ns_system::GameObject("character_test")
		{
			m_pAudSrc = &addComponent<ns_system::AudioSource>(ns_system::AudioSource("breakout"));
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

		void CharacterTest::render()
		{
			/*m_pShader->bind();

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
			glBindVertexArray(0);*/

			GameObject::render();
		};
	}