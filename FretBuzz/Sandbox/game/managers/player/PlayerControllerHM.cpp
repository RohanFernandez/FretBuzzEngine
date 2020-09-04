#include <fretbuzz_pch.h>
#include "PlayerControllerHM.h"
#include <input.h>
#include <system/scene_manager.h>
#include "game/managers/weapon/weapon_data.h"
#include "game/managers/weapon/weapon_manager.h"
#include <fretbuzz.h>

namespace ns_HMGame
{
	PlayerControllerHM* PlayerControllerHM:: s_Instance = nullptr;;

	PlayerControllerHM::PlayerControllerHM(FRETBUZZ::GameObject* a_GameObject, FRETBUZZ::GameObject* a_pCamGameObject, FRETBUZZ::GameObject* a_pPlayerUpperGameObj, FRETBUZZ::GameObject* a_pLegsGameObject)
		: FRETBUZZ::Behaviour(a_GameObject),
		m_WeaponData{WeaponManager::GetWeaponData(WEAPON_UNARMED)}
	{
		s_Instance = this;
		m_pPlayerUpperGameObj = a_pPlayerUpperGameObj;
		m_pGameObjCharacterLegs = a_pLegsGameObject;

		m_pRectCollider = a_GameObject->getComponent<FRETBUZZ::RectCollider>(FRETBUZZ::COMPONENT_TYPE::COLLIDER_2D);
		m_pCamGameObj = a_pCamGameObject;

		m_pLegsSpriteAnimator = a_pLegsGameObject->getComponent<FRETBUZZ::SpriteAnimationController >(FRETBUZZ::COMPONENT_TYPE::SPRITE_ANIMATION_CONTROLLER);
		m_pUpperSpriteAnimator = a_pPlayerUpperGameObj->getComponent<FRETBUZZ::SpriteAnimationController>(FRETBUZZ::COMPONENT_TYPE::SPRITE_ANIMATION_CONTROLLER);
	}

	void PlayerControllerHM::update(const float& a_fDeltaTime)
	{
		manageInput(a_fDeltaTime);
		Behaviour::update(a_fDeltaTime);
	}

	void PlayerControllerHM::manageInput(float a_fDeltaTime)
	{
		float l_fHorizontalVelocity = 0.0f;
		float l_fVerticalVelocity = 0.0f;

		if (FRETBUZZ::Input::IsKeyDown(GLFW_KEY_W))
		{
			l_fVerticalVelocity += m_fVelocity;
		}

		if (FRETBUZZ::Input::IsKeyDown(GLFW_KEY_S))
		{
			l_fVerticalVelocity -= m_fVelocity;
		}
		if (FRETBUZZ::Input::IsKeyDown(GLFW_KEY_A))
		{
			l_fHorizontalVelocity -= m_fVelocity;
		}
		if (FRETBUZZ::Input::IsKeyDown(GLFW_KEY_D))
		{
			l_fHorizontalVelocity += m_fVelocity;
		}

		FRETBUZZ::Input::GetMousePosition(m_dMouseX, m_dMouseY);
		glm::vec2 l_MousePosition = glm::vec2((float)m_dMouseX - (FRETBUZZ::Window::getWidth() * 0.5f), (FRETBUZZ::Window::getHeight() * 0.5f) - (float)m_dMouseY);
		glm::vec2 l_v2PlayerToMouseDirection = glm::normalize(l_MousePosition);
		float a_fZ = glm::atan(l_v2PlayerToMouseDirection.x, l_v2PlayerToMouseDirection.y);
		m_pPlayerUpperGameObj->m_Transform.setLocalRotation({ 0.0f, 0.0f, -a_fZ + M_PI_2 });

		std::string l_strPlayerAnimTrigger = "idle";

		float l_fRotationZ = 0.0f;
		if (l_fHorizontalVelocity != 0.0f || l_fVerticalVelocity != 0.0f)
		{
			l_strPlayerAnimTrigger = "walk";
			if (l_fHorizontalVelocity != 0.0f &&
				l_fVerticalVelocity != 0.0f)
			{
				l_fHorizontalVelocity *= 0.75f;
				l_fVerticalVelocity *= 0.75f;

				l_fRotationZ = (float)(l_fHorizontalVelocity > 0.0f ? M_PI_4 : (M_PI_2 + M_PI_4));
				if (l_fVerticalVelocity < 0.0f)
				{
					l_fRotationZ = -l_fRotationZ;
				}
			}
			else if (l_fHorizontalVelocity == 0.0f)
			{
				l_fRotationZ = (float)(l_fVerticalVelocity > 0.0f ? M_PI_2 : -M_PI_2);
			}
			else if (l_fVerticalVelocity == 0.0f)
			{
				l_fRotationZ = (float)(l_fHorizontalVelocity > 0.0f ? 0.0f : M_PI);
			}

			float l_fDotMovementToFace = glm::dot(l_v2PlayerToMouseDirection, glm::normalize(glm::vec2{ l_fHorizontalVelocity , l_fVerticalVelocity }));
			// If movement is opposite direction fo cursor face, the rotate legs by 180 so shoes are always pointing to cursor face.
			if (l_fDotMovementToFace < -0.5)
			{
				l_fRotationZ += (float)(M_PI);
			}
			m_pGameObjCharacterLegs->m_Transform.setLocalRotation({ 0.0f, 0.0f, l_fRotationZ});
		}

		m_pUpperSpriteAnimator->play(l_strPlayerAnimTrigger);
		m_pLegsSpriteAnimator->play(l_strPlayerAnimTrigger);
		m_pRectCollider->setLinearVelocity(glm::vec2{ l_fHorizontalVelocity, l_fVerticalVelocity });
		m_pCamGameObj->m_Transform.setWorldPosition(m_GameObject.m_Transform.getWorldPosition());

		//std::cout << "x: "<<l_v2PlayerToMouseDirection.x << "\ty: " << l_v2PlayerToMouseDirection.y << "\n";

		//// DEBUG START //// 
		if (FRETBUZZ::Input::IsKeyPutDown(GLFW_KEY_L))
		{
			FRETBUZZ::SceneManager::LogSceneHierarchy();
		}
		//// DEBUG END ////
		if (FRETBUZZ::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_1))
		{
			m_pUpperSpriteAnimator->play("attack");
			glm::vec3 l_v3PlayerPosition = m_GameObject.m_Transform.getWorldPosition();
			m_WeaponData.fire(glm::vec2{l_v3PlayerPosition.x, l_v3PlayerPosition.y} +l_v2PlayerToMouseDirection * 150.0f, l_v2PlayerToMouseDirection, m_pPlayerUpperGameObj->m_Transform.getLocalRotation());

			/*FRETBUZZ::Collider2D* l_pCollider2D = nullptr;
			glm::vec2 l_v2PlayerPosition = m_GameObject.m_Transform.getWorldPosition();
			glm::vec2 l_v2MouseWorldPosition = l_v2PlayerPosition + l_MousePosition;

			FRETBUZZ::PhysicsEngine::Raycast(l_pCollider2D, l_v2PlayerPosition, l_v2MouseWorldPosition);

			if (l_pCollider2D != nullptr)
			{
				InteractiveObject* l_pInteractiveObject = l_pCollider2D->m_GameObject.getComponent<InteractiveObject>(FRETBUZZ::COMPONENT_TYPE::BEHAVIOUR);
				if (l_pInteractiveObject != nullptr)
				{
					l_pInteractiveObject->onLabelHit();
				}
			}*/
		}
		else if (FRETBUZZ::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_2))
		{
			WEAPON_TYPE l_CurrentWeaponType = m_WeaponData.getWeaponType();
			if (l_CurrentWeaponType != WEAPON_TYPE::WEAPON_UNARMED)
			{
				Weapon* l_pWeaponToThrow = WeaponManager::AddWeapon(m_GameObject.m_Transform.getWorldPosition() + glm::vec3(l_v2PlayerToMouseDirection, 0.0f) * 50.0f, l_CurrentWeaponType,true);
				l_pWeaponToThrow->startWeaponThrow(l_v2PlayerToMouseDirection);

				m_WeaponData = WeaponManager::GetWeaponData(WEAPON_TYPE::WEAPON_UNARMED);
				m_pUpperSpriteAnimator->play(m_WeaponData.getWeaponAnimTrigger());
			}

			if (m_vectWeaponOver.size() > 0)
			{
				m_WeaponData = m_vectWeaponOver[0]->getWeaponData();
				m_pUpperSpriteAnimator->play(m_WeaponData.getWeaponAnimTrigger());
				m_vectWeaponOver[0]->pickup();
			}
			APP_ERROR("Tracing weapon throw");
		}
		else if (FRETBUZZ::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_3))
		{
			m_pUpperSpriteAnimator->play("snap");
		}
	}

	void PlayerControllerHM::onCollisionEnter2D(FRETBUZZ::Collider2D* a_pIComponent)
	{
		//std::cout << "PlayerController::OnCollisionEnter2D:: " << a_pIComponent->m_GameObject.getName() << "\n";
	}

	void PlayerControllerHM::onCollisionExit2D(FRETBUZZ::Collider2D* a_pIComponent)
	{
		//std::cout << "PlayerController::OnCollisionExit2D:: " << a_pIComponent->m_GameObject.getName() << "\n";
	}

	void PlayerControllerHM::onTriggerEnter2D(FRETBUZZ::Collider2D* a_pIComponent)
	{
		//std::cout << "PlayerController::OnTriggerEnter2D:: " << a_pIComponent->m_GameObject.getName() << "\n";
	}

	void PlayerControllerHM::onTriggerExit2D(FRETBUZZ::Collider2D* a_pIComponent)
	{
		//std::cout << "PlayerController::OnTriggerExit2D:: " << a_pIComponent->m_GameObject.getName() << "\n";
	}

	void PlayerControllerHM::setAsCurrentWeaponOver(ns_HMGame::Weapon* a_pWeapon, bool a_bIsOver)
	{
		if (a_bIsOver) { addToWeaponOver(a_pWeapon); }
		else { removeFromWeaponOver(a_pWeapon); }
	}

	void PlayerControllerHM::addToWeaponOver(Weapon* a_Weapon)
	{
		m_vectWeaponOver.emplace_back(a_Weapon);
	}

	void PlayerControllerHM::removeFromWeaponOver(Weapon* a_Weapon)
	{
		auto it = std::find(m_vectWeaponOver.begin(), m_vectWeaponOver.end(), a_Weapon);
		if (it != m_vectWeaponOver.end())
		{
			m_vectWeaponOver.erase(it);
		}
	}
}