#pragma once
#include "../system/scene_manager.h"
#include "../system/game_object.h"
#include "../test/CharacterTest.h"

namespace ns_fretBuzz
{
	class MainMenuState 
		: public ns_system::IScene
	{
	public:
		ns_system::GameObject m_goParentGameObj;
		CharacterTest m_CharacterTest;

		MainMenuState(std::string a_strSceneName) :
			IScene(a_strSceneName),
			m_goParentGameObj("parent", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }),
			m_CharacterTest()
		{
			m_refRootGameObject.addChild(&m_goParentGameObj);
			m_goParentGameObj.addChild(&m_CharacterTest);
		}

		virtual void OnStateEnter() override
		{
			IScene::OnStateEnter();
		}

		virtual void OnStateExit() override
		{
			IScene::OnStateExit();
		}
	};
}