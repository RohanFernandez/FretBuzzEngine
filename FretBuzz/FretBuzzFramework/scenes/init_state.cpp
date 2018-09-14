#pragma once

#include "../framework/system/core/resource_manager.h"
#include "../framework/system/core/window.h"
#include "../framework/components/viewport.h"

#include "init_state.h"

namespace ns_fretBuzz
{
	InitState::InitState(std::string a_strSceneName) :
		IScene(a_strSceneName)
	{

		ns_system ::GameObject* l_pLabelGameObj1 = ns_system::GameObject::instantiate(m_refRootGameObject, "LABEL1", { -300.0f, -50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f/*M_PI*/ }, { 1.0f, 1.0f, 1.0f }, true);
		ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj1, { 0.0f, 1.0f, 0.0f,1.0f }, { 175.0f, 80.0f });
		ns_system::RectCollider::addToGameObject(*l_pLabelGameObj1, { 175.0f, 80.0f });

		ns_system::GameObject* l_pLabelGameObj2 = ns_system::GameObject::instantiate(*l_pLabelGameObj1, "LABEL2", { 150.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f },true);
		ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj2, { 1.0f, 1.0f, 0.0f,1.0f }, { 180.0f, 90.0f });
		ns_system::RectCollider::addToGameObject(*l_pLabelGameObj2, { 180.0f, 90.0f });

		ns_system::GameObject* l_pLabelGameObj3 = ns_system::GameObject::instantiate(*l_pLabelGameObj2, "LABEL3", { 150.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, true);
		ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj3, { 0.8f, 0.3f, 0.5f,1.0f }, { 150.0f, 100.0f });
		ns_system::RectCollider::addToGameObject(*l_pLabelGameObj3, { 150.0f, 100.0f });

		ns_system::GameObject* l_pLabelGameObj4 = ns_system::GameObject::instantiate(*l_pLabelGameObj3, "LABEL4", { 150.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, true);
		ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj4, { 0.0f, 1.0f, 1.0f,1.0f }, { 150.0f, 100.0f });
		ns_system::RectCollider::addToGameObject(*l_pLabelGameObj4, { 150.0f, 100.0f });

		ns_system::GameObject* l_pLabelGameObj5 = ns_system::GameObject::instantiate(*l_pLabelGameObj4, "LABEL5", { 150.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, true);
		ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj5, { 1.0f, 0.0f, 1.0f,1.0f }, { 150.0f, 100.0f });
		ns_system::RectCollider::addToGameObject(*l_pLabelGameObj5, { 150.0f, 100.0f });

		//ns_system::GameObject* l_pLabelGameObj6 = ns_system::GameObject::instantiate(*l_pLabelGameObj5, "LABEL6", { 150.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, true);
		//ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj6, { 1.0f, 1.0f, 1.0f,1.0f }, { 150.0f, 100.0f });
		//ns_system::RectCollider::addToGameObject(*l_pLabelGameObj6, { 150.0f, 100.0f });

		CharacterTest* l_gameObjChar = new CharacterTest(m_refRootGameObject, "character_test");

		ns_system::GameObject* l_pLabelGameObj6 = ns_system::GameObject::instantiate(*l_gameObjChar, "LABEL6", { 150.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, true);
		ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj6, { 1.0f, 1.0f, 1.0f,1.0f }, { 150.0f, 100.0f });
		//ns_system::RectCollider::addToGameObject(*l_pLabelGameObj6, { 150.0f, 100.0f });
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
