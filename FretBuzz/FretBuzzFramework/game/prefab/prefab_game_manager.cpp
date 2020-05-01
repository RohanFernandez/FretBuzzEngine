#include <fretbuzz_pch.h>
#include "prefab_game_manager.h"
#include <components/gameobject_components/audio_source.h>
#include "game/managers/weapon/weapon_manager.h"
#include "system/game_object.h"

namespace ns_HMGame
{
	PrefabGameManager::PrefabGameManager(ns_fretBuzz::ns_system::GameObject& a_ParentGameObject, std::string a_strName)
		: ns_fretBuzz::ns_system::GameObject(a_ParentGameObject, a_strName, ns_fretBuzz::ns_system::Layer(),true)
	{
		auto l_pAudSrc = this->addComponent<ns_fretBuzz::ns_system::AudioSource>("beats", true);
		this->addComponent<WeaponManager>();
	}
}