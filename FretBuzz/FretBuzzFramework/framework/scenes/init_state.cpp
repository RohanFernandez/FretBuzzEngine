#pragma once

#include "../system/core/resource_manager.h"
#include "../system/core/window.h"
#include "../components/camera/camera.h"

#include "init_state.h"



namespace ns_fretBuzz
{
	InitState::InitState(std::string a_strSceneName) :
		IScene(a_strSceneName),
		m_goParentGameObj("parent", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }),
		m_CharacterTest()
	{
		m_refRootGameObject.addChild(&m_goParentGameObj);
		m_goParentGameObj.addChild(&m_CharacterTest);
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