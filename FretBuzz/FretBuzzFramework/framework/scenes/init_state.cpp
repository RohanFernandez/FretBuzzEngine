#pragma once

#include "../system/core/resource_manager.h"
#include "../system/core/window.h"
#include "../components/camera.h"

#include "init_state.h"



namespace ns_fretBuzz
{
	InitState::InitState(std::string a_strSceneName) :
		IScene(a_strSceneName)
	{
		m_goParentGameObj = ns_system::GameObject::instantiate(m_refRootGameObject, "parent", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f });
		m_CharacterTest = new CharacterTest(*m_goParentGameObj, "character_test");
	}

	void InitState::OnStateEnter()
	{
		IScene::OnStateEnter();
	}

	void InitState::OnStateExit()
	{
		IScene::OnStateExit();
	}
}