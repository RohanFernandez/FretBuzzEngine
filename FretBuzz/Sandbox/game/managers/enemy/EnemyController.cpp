#include <fretbuzz_pch.h>
#include "EnemyController.h"
#include "game/managers/weapon/weapon_data.h"
#include "game/managers/weapon/weapon_manager.h"
#include "game/managers/player/PlayerControllerHM.h"

namespace ns_HMGame
{
	EnemyController::EnemyController(ns_fretBuzz::GameObject* a_GameObject, ns_fretBuzz::GameObject* a_pPlayerUpperGameObj, ns_fretBuzz::GameObject* a_pLegsGameObject)
		: ns_fretBuzz::Behaviour(a_GameObject),
		m_WeaponData{ WeaponManager::GetWeaponData(WEAPON_M16) }
	{
		m_pPlayerUpperGameObj = a_pPlayerUpperGameObj;
		m_pGameObjCharacterLegs = a_pLegsGameObject;

		m_pRectCollider = a_GameObject->getComponent<ns_fretBuzz::RectCollider>(ns_fretBuzz::COMPONENT_TYPE::COLLIDER_2D);

		m_pLegsSpriteAnimator = a_pLegsGameObject->getComponent<ns_fretBuzz::SpriteAnimationController >(ns_fretBuzz::COMPONENT_TYPE::SPRITE_ANIMATION_CONTROLLER);
		m_pUpperSpriteAnimator = a_pPlayerUpperGameObj->getComponent<ns_fretBuzz::SpriteAnimationController>(ns_fretBuzz::COMPONENT_TYPE::SPRITE_ANIMATION_CONTROLLER);
	}

	void EnemyController::update(const float& a_fDeltaTime)
	{
		manageAI(a_fDeltaTime);
		Behaviour::update(a_fDeltaTime);
	}

	void EnemyController::manageAI(float a_fDeltaTime)
	{
		bool l_bIsShoot = false;
		m_fTimeSinceLastShot += a_fDeltaTime;
		if (m_fTimeSinceLastShot > MIN_TIME_BETWEEN_GUNSHOT)
		{
			m_fTimeSinceLastShot = 0.0f;
			l_bIsShoot = true;
		}

		glm::vec3 l_v3EnemyPostion = m_GameObject.m_Transform.getWorldPosition();
		PlayerControllerHM* l_PlayerInstance = PlayerControllerHM::GetInstance();

		if (l_PlayerInstance == nullptr)
		{
			return;
		}
		glm::vec3 l_v3PlayerPostion = l_PlayerInstance->m_GameObject.m_Transform.getWorldPosition();
		ns_fretBuzz::Collider2D* l_pRaycastResult = nullptr;

		ns_fretBuzz::PhysicsEngine::Raycast(l_pRaycastResult, { l_v3EnemyPostion.x, l_v3EnemyPostion.y }, { l_v3PlayerPostion.x, l_v3PlayerPostion.y});

		if (l_pRaycastResult == nullptr)
		{
			return;
		}

		PlayerControllerHM* m_pPLayerController = l_pRaycastResult->m_GameObject.getComponent<PlayerControllerHM>(ns_fretBuzz::COMPONENT_TYPE::BEHAVIOUR);
		if (m_pPLayerController != nullptr)
		{
			glm::vec3 l_v3EnemyToPlayerDirection = glm::normalize(l_v3PlayerPostion - l_v3EnemyPostion);
			float a_fZ = glm::atan(l_v3EnemyToPlayerDirection.x, l_v3EnemyToPlayerDirection.y);
			m_pPlayerUpperGameObj->m_Transform.setLocalRotation({ 0.0f, 0.0f, -a_fZ + M_PI_2 });

			if (l_bIsShoot)
			{
				m_WeaponData.fire(l_v3EnemyPostion + l_v3EnemyToPlayerDirection * 100.0f, l_v3EnemyToPlayerDirection, m_GameObject.m_Transform.getLocalRotation());
			}
		}
	}
}