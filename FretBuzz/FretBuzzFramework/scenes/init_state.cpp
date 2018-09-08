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
		CharacterTest* l_gameObjChar = new CharacterTest(m_refRootGameObject, "character_test");

		ns_system ::GameObject* l_pLabelGameObj1 = ns_system::GameObject::instantiate(m_refRootGameObject, "LABEL1", { 200.0f, -200.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f });
		ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj1, { 0.0f, 1.0f, 0.0f,1.0f }, { 175.0f, 80.0f });
		ns_system::RectCollider::addToGameObject(*l_pLabelGameObj1, { 175.0f, 80.0f });

		ns_system::GameObject* l_pLabelGameObj2 = ns_system::GameObject::instantiate(m_refRootGameObject, "LABEL2", { -250.0f, 250.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f });
		ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj2, { 1.0f, 1.0f, 0.0f,1.0f }, { 180.0f, 90.0f });
		ns_system::RectCollider::addToGameObject(*l_pLabelGameObj2, { 180.0f, 90.0f });

		ns_system::GameObject* l_pLabelGameObj3 = ns_system::GameObject::instantiate(m_refRootGameObject, "LABEL3", { 200.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f });
		ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj3, { 0.8f, 0.3f, 0.5f,1.0f }, { 100.0f, 200.0f });
		ns_system::RectCollider::addToGameObject(*l_pLabelGameObj3, { 100.0f, 200.0f });

		ns_system::GameObject* l_pLabelGameObj4 = ns_system::GameObject::instantiate(m_refRootGameObject, "LABEL4", { -200.0f, -200.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f });
		ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj4, { 0.0f, 1.0f, 1.0f,1.0f }, { 150.0f, 100.0f });
		ns_system::RectCollider::addToGameObject(*l_pLabelGameObj4, { 150.0f, 100.0f });
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