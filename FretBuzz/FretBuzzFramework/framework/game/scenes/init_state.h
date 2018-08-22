#pragma once
#include "../../system/scene_manager.h"
#include "../../graphics/shader.h"
#include "../../graphics/texture.h"

#include "../../test/CharacterTest.h"

namespace ns_fretBuzz
{
	class InitState : 
		public ns_system::IScene
	{
	public:
		
		CharacterTest m_CharacterTest;

		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_IBO;
		bool isAudioPlaying = false;

		InitState(std::string a_strSceneName);
			
		virtual void OnStateEnter() override;

		virtual void OnStateExit() override;

		

		/*virtual void render() override
		{
			m_pShader->bind();

			m_pShader->setUniforMat4fv("unifProjection", m_Camera.getProjectionMatrix());
			m_pShader->setUniforMat4fv("unifView", m_Camera.getViewMatrix());

			glm::mat4 l_mat4SpriteModel = glm::mat4(1.0f);
			l_mat4SpriteModel = glm::translate(l_mat4SpriteModel, {0.0f, 0.0f, 0.0f});
			l_mat4SpriteModel = glm::scale(l_mat4SpriteModel, {600.0f, 400.0f, 0.0f});

			m_pShader->setUniforMat4fv("unifModel", (l_mat4SpriteModel));

			ns_system::Window::CheckForErrors();

			glActiveTexture(GL_TEXTURE0);
			m_pTexture->bind();

			m_pShader->setUniform1i("textureSampler", 0);

			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}*/
	};
}