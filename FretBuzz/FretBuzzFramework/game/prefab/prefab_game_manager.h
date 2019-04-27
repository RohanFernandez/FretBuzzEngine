#pragma once

#include "system/game_object.h" 

namespace ns_HMGame
{
	class FRETBUZZ_API PrefabGameManager : public ns_fretBuzz::ns_system::GameObject
	{
	public:
		PrefabGameManager(ns_fretBuzz::ns_system::GameObject& a_ParentGameObject, std::string a_strName);
	};
}