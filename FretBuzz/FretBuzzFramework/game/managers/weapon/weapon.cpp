#include <fretbuzz_pch.h>
#include "weapon.h"
#include <system/core/resource_manager.h>
#include <game/managers/player/PlayerController.h>
#include "weapon_manager.h"

namespace ns_HMGame
{
	Weapon::Weapon(ns_fretBuzz::ns_system::GameObject2D* a_pGameObject)
		:m_WeaponType{ WEAPON_TYPE::WEAPON_UNARMED },
		ns_fretBuzz::ns_system::Behaviour(a_pGameObject)
	{
		m_pSpriteRenderer = m_GameObject.getComponent<ns_fretBuzz::ns_graphics::SpriteRenderer>(ns_fretBuzz::ns_system::COMPONENT_TYPE::SPRITE_RENDERER);
		m_pSpriteRenderer->setSprite(ns_fretBuzz::ns_system::ResourceManager::getResource<ns_fretBuzz::ns_graphics::SpriteGroup>("weapon_pickup|weapon_M16")->getSprite(0));
	}

	void Weapon::setWeapon(WEAPON_TYPE a_WeaponType)
	{
		m_WeaponType = a_WeaponType;
	}

	void Weapon::onTriggerEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent)
	{
		//std::cout << "PlayerController::OnTriggerEnter2D:: " << a_pIComponent->m_GameObject.getName() << "\n";
		ns_HMGame::PlayerController* l_pPlayerController = a_pIComponent->m_GameObject.getComponent<ns_HMGame::PlayerController>(ns_fretBuzz::ns_system::COMPONENT_TYPE::BEHAVIOUR);
		if (l_pPlayerController != nullptr)
		{
			l_pPlayerController->setAsCurrentWeapon(this);
		}
	}

	void Weapon::onTriggerExit2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent)
	{
		ns_HMGame::PlayerController* l_pPlayerController = a_pIComponent->m_GameObject.getComponent<ns_HMGame::PlayerController>(ns_fretBuzz::ns_system::COMPONENT_TYPE::BEHAVIOUR);
		if (l_pPlayerController != nullptr)
		{
			l_pPlayerController->setAsCurrentWeapon(nullptr);
		}
	}
}