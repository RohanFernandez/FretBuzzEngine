#pragma once
#include "../framework/system/scene_manager.h"

namespace ns_fretBuzz
{
	class ScoreState 
		: public ns_system::IScene
	{
	public:
		ScoreState(std::string a_strSceneName) :
			IScene(a_strSceneName)
		{
			ns_system::GameObject::instantiate(m_refRootGameObject, "score_!!!!!!", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f })->setAsDontDestroy();
		}

	};
}