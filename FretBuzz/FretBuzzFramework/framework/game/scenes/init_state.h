#pragma once
#include "../../system/managers/scene_manager.h"
#include "../../system/managers/resource_manager.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../../system/window.h"

namespace ns_fretBuzz
{
	class InitState : 
		public ns_system::IScene,
		public ns_system::IUpdateTimer
	{
	public:
		const ns_graphics::Shader* m_pShader = nullptr;
		const ns_graphics::Texture* m_pTexture = nullptr;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_IBO;

		GLfloat m_vertices[20] = 
		{
			-0.5, -0.5, 1.0, 0.0, 0.0,
			-0.5, 0.5, 1.0, 0.0, 1.0,
			 0.5, 0.5, 1.0, 1.0, 1.0,
			 0.5, -0.5, 1.0, 1.0, 0.0
		};

		GLuint m_indices[6] =
		{
			0, 1, 2,
			2, 3, 0
		};

		InitState(std::string a_strSceneName) :
			IScene(a_strSceneName),
			ns_system::IUpdateTimer()
		{
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

		virtual void OnStateEnter() override
		{
			IScene::OnStateEnter();
		}

		virtual void OnStateExit() override
		{
			IScene::OnStateExit();
		}

		virtual void onUpdate(const float a_fDeltaTime) override
		{
			/*std::cout << "Update :: InitState state\n";*/
		}

		virtual void onLateUpdate(const float a_fDeltaTime) override
		{
			/*std::cout << "LateUpdate :: InitState state\n";*/
		}

		virtual void render() override
		{
			m_pShader->bind();
			ns_system::Window::CheckForErrors();

			glActiveTexture(GL_TEXTURE0);
			m_pTexture->bind();

			m_pShader->setUniform1i("textureSampler", 0);

			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	};
}