#pragma once

#include "system/game_object.h" 

namespace ns_HMGame
{
	class PrefabGameManager : public ns_fretBuzz::GameObject
	{
	public:
		PrefabGameManager(ns_fretBuzz::GameObject& a_ParentGameObject, std::string a_strName);
	};
}