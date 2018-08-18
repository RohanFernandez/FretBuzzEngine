#pragma once

#include "../../system/resource_manager.h"
#include "../../system/window.h"

#include "init_state.h"



namespace ns_fretBuzz
{
	InitState::InitState(std::string a_strSceneName) :
		IScene(a_strSceneName),
		m_Camera{ glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f,180.0f,0.0f }, glm::vec3{ 1.0f,1.0f,1.0f }, -(float)ns_system::Window::getWidth() / 2.0f, (float)ns_system::Window::getWidth() / 2.0f, -(float)ns_system::Window::getHeight() / 2.0f, (float)ns_system::Window::getHeight() / 2.0f, -1.0f, 1.0f }
		//m_Camera{ glm::vec3{ 0.0f,0.0f,3.0f }, glm::vec3{ 0.0f,180.0f,0.0f }, glm::vec3{ 1.0f,1.0f,1.0f }, 45.0f, 0.01f, 100.0f }
		, m_CharacterTest()
	{
		m_pShader = ns_system::ResourceManager::getResource<ns_graphics::Shader>("tShader");
		m_pTexture = ns_system::ResourceManager::getResource<ns_graphics::Texture>("darksider");

		m_gameObjectRoot.addChild(&m_CharacterTest);

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

	void InitState::OnStateEnter()
	{
		IScene::OnStateEnter();
	}

	void InitState::OnStateExit()
	{
		IScene::OnStateExit();
	}

	//virtual void onUpdate(const float a_fDeltaTime) override
	//{
	//	/*std::cout << "Update :: InitState state\n";*/

	//	m_Camera.m_transform.translate(m_Camera.m_transform.getPosition() + glm::vec3{a_fDeltaTime * 35.0f,0.0f,0.0f});


	//	if (ns_system::Input::IsKeyDown(GLFW_KEY_G))
	//	{
	//		m_AudSrc.play();
	//	}
	//	
	//	if (ns_system::Input::IsKeyDown(GLFW_KEY_H))
	//	{
	//		m_AudSrc.restart();
	//	}

	//	if (ns_system::Input::IsKeyDown(GLFW_KEY_J))
	//	{
	//		m_AudSrc.stop();
	//	}

	//	if (ns_system::Input::IsKeyDown(GLFW_KEY_K))
	//	{
	//		m_AudSrc.pause();
	//	}
	//}

	//virtual void onLateUpdate(const float a_fDeltaTime) override
	//{
	//	/*std::cout << "LateUpdate :: InitState state\n";*/
	//}

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
}