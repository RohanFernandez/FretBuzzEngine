#pragma once

#include "../../system/resource_manager.h"
#include "../../system/window.h"
#include "../../components/camera/camera.h"

#include "init_state.h"



namespace ns_fretBuzz
{
	InitState::InitState(std::string a_strSceneName) :
		IScene(a_strSceneName),
		m_CharacterTest()
	{
		m_refRootGameObject.addChild(&m_CharacterTest);
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