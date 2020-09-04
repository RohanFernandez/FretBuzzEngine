#include <fretbuzz_pch.h>
#include "prefab_game_manager.h"
#include <components/gameobject_components/audio_source.h>
#include "game/managers/weapon/weapon_manager.h"
#include "system/game_object.h"

namespace ns_HMGame
{
	PrefabGameManager::PrefabGameManager(FRETBUZZ::GameObject& a_ParentGameObject, std::string a_strName)
		: FRETBUZZ::GameObject(a_ParentGameObject, a_strName)
	{
		auto l_pAudSrc = this->addComponent<FRETBUZZ::AudioSource>("beats", true);
		l_pAudSrc->setVolume(0.0f);
		this->addComponent<WeaponManager>();
	}
}