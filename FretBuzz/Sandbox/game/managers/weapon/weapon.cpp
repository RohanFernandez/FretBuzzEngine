#include <fretbuzz_pch.h>
#include "weapon.h"
#include <system/core/resource_manager.h>
#include <game/managers/player/PlayerControllerHM.h>
#include "weapon_manager.h"

namespace ns_HMGame
{
	Weapon::Weapon(ns_fretBuzz::ns_system::GameObject2D* a_pGameObject)
		:
		ns_fretBuzz::ns_system::Behaviour(a_pGameObject),
		m_WeaponData{ WeaponManager::GetWeaponData(WEAPON_TYPE::WEAPON_UNARMED)},
		m_CurrentWeaponState{WEAPON_STATE::DROP}
	{
		m_pSpriteRenderer = m_GameObject.getComponent<ns_fretBuzz::ns_graphics::SpriteRenderer>(ns_fretBuzz::ns_system::COMPONENT_TYPE::SPRITE_RENDERER);
		m_pSpriteRenderer->setSprite(ns_fretBuzz::ns_system::ResourceManager::getResource<ns_fretBuzz::ns_graphics::SpriteGroup>("weapon_pickup|weapon_M16")->getSprite(0));

		m_pCollider2D = m_GameObject.getComponent<ns_fretBuzz::ns_system::Collider2D>(ns_fretBuzz::ns_system::COMPONENT_TYPE::COLLIDER_2D);

		setWeaponState(m_CurrentWeaponState);
	}

	void Weapon::setWeapon(WEAPON_TYPE a_WeaponType)
	{
		m_WeaponData = WeaponManager::GetWeaponData(a_WeaponType);
		m_pSpriteRenderer->setSprite(m_WeaponData.getWeaponSpriteName());
	}

	WeaponData Weapon::getWeaponData()
	{
		return m_WeaponData;
	}

	void Weapon::onTriggerEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent)
	{
		//std::cout << "PlayerController::OnTriggerEnter2D:: " << a_pIComponent->m_GameObject.getName() << "\n";
		ns_HMGame::PlayerControllerHM* l_pPlayerController = a_pIComponent->m_GameObject.getComponent<ns_HMGame::PlayerControllerHM>(ns_fretBuzz::ns_system::COMPONENT_TYPE::BEHAVIOUR);
		if (l_pPlayerController != nullptr)
		{
			l_pPlayerController->setAsCurrentWeaponOver(this, true);
		}
	}

	void Weapon::startWeaponThrow(glm::vec2 a_v2PlayerToMouseDirection)
	{
		setWeaponState(WEAPON_STATE::THROWN);
		m_pCollider2D->setLinearVelocity(a_v2PlayerToMouseDirection * 700.0f);
	}

	void Weapon::pickup()
	{
		setWeaponState(WEAPON_STATE::IN_USE);
	}

	void Weapon::setWeaponState(WEAPON_STATE a_State)
	{
		m_CurrentWeaponState = a_State;
		switch (m_CurrentWeaponState)
		{
			case WEAPON_STATE::DROP:
			{
				m_pCollider2D->setSensor(true);
				m_pCollider2D->addCollisionLayer("PLAYER");
				m_pCollider2D->setFixedRotation(false);
				m_pCollider2D->setPhysicsBodyType(ns_fretBuzz::ns_system::PHYSICS_BODY_TYPE::STATIC);
				break;
			}
			case WEAPON_STATE::IN_USE:
			{
				m_GameObject.setActive(false);
				WeaponManager::ReturnWeaponToPool(reinterpret_cast<PrefabWeapon*>(&m_GameObject));
				break;
			}
			case WEAPON_STATE::THROWN:
			{
				m_pCollider2D->setSensor(false);
				m_pCollider2D->removeCollisionLayer("PLAYER");
				m_pCollider2D->setPhysicsBodyType(ns_fretBuzz::ns_system::PHYSICS_BODY_TYPE::DYNAMIC);
				m_pCollider2D->setFixedRotation(false);
				m_pCollider2D->setAngularVelocity((float)M_PI);
				m_pCollider2D->setDensity(1.0f);
				m_GameObject.setActive(true);
				break;
			}
		}
	}

	void Weapon::onCollisionEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent)
	{
	}

	void Weapon::onCollisionExit2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent)
	{
	}

	void Weapon::onTriggerExit2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent)
	{
		ns_HMGame::PlayerControllerHM* l_pPlayerController = a_pIComponent->m_GameObject.getComponent<ns_HMGame::PlayerControllerHM>(ns_fretBuzz::ns_system::COMPONENT_TYPE::BEHAVIOUR);
		if (l_pPlayerController != nullptr)
		{
			l_pPlayerController->setAsCurrentWeaponOver(this, false);
		}
	}

	void Weapon::update(const float& a_fDeltaTime)
	{
		if (WEAPON_STATE::THROWN == m_CurrentWeaponState)
		{
			if (glm::length(m_pCollider2D->getLinearVelocity()) < 120.0f)
			{
				setWeaponState(WEAPON_STATE::DROP);
			}
		}
	}
}