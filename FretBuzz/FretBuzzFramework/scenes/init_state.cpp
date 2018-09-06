#pragma once

#include "../framework/system/core/resource_manager.h"
#include "../framework/system/core/window.h"
#include "../framework/components/camera.h"

#include "init_state.h"

namespace ns_fretBuzz
{
	InitState::InitState(std::string a_strSceneName) :
		IScene(a_strSceneName)
	{
		ns_system :: GameObject* l_pLabelGameObj = ns_system::GameObject::instantiate(m_refRootGameObject, "LABEL", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f });
		ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj, { 0.0f, 1.0f, 0.0f,1.0f }, { 100.0f, 100.0f });
		CharacterTest* l_gameObjChar = new CharacterTest(m_refRootGameObject, "character_test");
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