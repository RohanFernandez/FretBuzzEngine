#include <fretbuzz_pch.h>
#include "prefab_game_manager.h"
#include <components/gameobject_components/audio_source.h>
#include "game/managers/weapon/weapon_manager.h"

namespace ns_HMGame
{
	PrefabGameManager::PrefabGameManager(ns_fretBuzz::ns_system::GameObject& a_ParentGameObject, std::string a_strName)
		: ns_fretBuzz::ns_system::GameObject(a_ParentGameObject, a_strName, true)
	{
		ns_fretBuzz::ns_system::AudioSource* l_pAudSrc = ns_fretBuzz::ns_system::AudioSource::addToGameObject(*this, "beats");
		ns_fretBuzz::ns_system::Behaviour::addToGameObject<WeaponManager>(*this);

		l_pAudSrc->setLooping(true);
		l_pAudSrc->play();


	}
}