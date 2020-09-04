#pragma once

#include "system/game_object.h" 

namespace ns_HMGame
{
	class PrefabGameManager : public FRETBUZZ::GameObject
	{
	public:
		PrefabGameManager(FRETBUZZ::GameObject& a_ParentGameObject, std::string a_strName);
	};
}