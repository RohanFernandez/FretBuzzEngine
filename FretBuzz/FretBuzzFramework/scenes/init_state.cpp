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
		m_goParentGameObj = ns_system::GameObject::instantiate(m_refRootGameObject, "parent", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f });

		ns_system::GameObject* m_pParent2 = ns_system::GameObject::instantiate(m_refRootGameObject, "parent2", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f });
		m_pParent2->setAsDontDestroy(true);

		ns_system::GameObject::instantiate(*m_pParent2, "child1", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f })->setAsDontDestroy(true);
		ns_system::GameObject* l_gameObj =  ns_system::GameObject::instantiate(*m_goParentGameObj, "child2", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f });
		CharacterTest* l_gameObjChar = new CharacterTest(*l_gameObj, "character_test");
		l_gameObjChar->setAsDontDestroy(true);

		ns_system::GameObject::instantiate(*m_goParentGameObj, "child3", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f })->setAsDontDestroy(true);
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