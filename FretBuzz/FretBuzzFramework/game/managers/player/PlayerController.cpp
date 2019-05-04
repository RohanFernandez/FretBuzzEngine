#include <fretbuzz_pch.h>
#include "PlayerController.h"
#include <system/core/input.h>
#include <system/scene_manager.h>

namespace ns_HMGame
{
	PlayerController::PlayerController(ns_fretBuzz::ns_system::GameObject& a_GameObject, ns_fretBuzz::ns_system::GameObject* a_pCamGameObject, ns_fretBuzz::ns_system::GameObject* a_pPlayerUpperGameObj, ns_fretBuzz::ns_system::GameObject* a_pLegsGameObject)
		: ns_fretBuzz::ns_system::Behaviour(a_GameObject)
	{
		m_pPlayerUpperGameObj = a_pPlayerUpperGameObj;
		m_pGameObjCharacterLegs = a_pLegsGameObject;

		m_pRectCollider = a_GameObject.getComponent<ns_fretBuzz::ns_system::RectCollider>(ns_fretBuzz::ns_system::COMPONENT_TYPE::COLLIDER_2D);
		m_pCamGameObj = a_pCamGameObject;

		m_pLegsSpriteAnimator = a_pLegsGameObject->getComponent<ns_fretBuzz::ns_system::SpriteAnimationController >(ns_fretBuzz::ns_system::COMPONENT_TYPE::SPRITE_ANIMATION_CONTROLLER);
		m_pUpperSpriteAnimator = a_pPlayerUpperGameObj->getComponent<ns_fretBuzz::ns_system::SpriteAnimationController>(ns_fretBuzz::ns_system::COMPONENT_TYPE::SPRITE_ANIMATION_CONTROLLER);
	}

	void PlayerController::update(float a_fDeltaTime)
	{
		manageInput();
		Behaviour::update(a_fDeltaTime);
	}

	void PlayerController::manageInput()
	{
		float l_fHorizontalVelocity = 0.0f;
		float l_fVerticalVelocity = 0.0f;

		if (ns_fretBuzz::ns_system::Input::IsKeyDown(GLFW_KEY_W))
		{
			l_fVerticalVelocity += m_fVelocity;
		}

		if (ns_fretBuzz::ns_system::Input::IsKeyDown(GLFW_KEY_S))
		{
			l_fVerticalVelocity -= m_fVelocity;
		}
		if (ns_fretBuzz::ns_system::Input::IsKeyDown(GLFW_KEY_A))
		{
			l_fHorizontalVelocity -= m_fVelocity;
		}
		if (ns_fretBuzz::ns_system::Input::IsKeyDown(GLFW_KEY_D))
		{
			l_fHorizontalVelocity += m_fVelocity;
		}

		ns_fretBuzz::ns_system::Input::GetMousePosition(m_dMouseX, m_dMouseY);
		glm::vec2 l_MousePosition = glm::vec2((float)m_dMouseX - (ns_fretBuzz::ns_graphics::Window::getWidth() * 0.5f), (ns_fretBuzz::ns_graphics::Window::getHeight() * 0.5f) - (float)m_dMouseY);
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
				l_fHorizontalVelocity *= 0.7f;
				l_fVerticalVelocity *= 0.7f;

				l_fRotationZ = l_fHorizontalVelocity > 0.0f ? M_PI_4 : (M_PI_2 + M_PI_4);
				if (l_fVerticalVelocity < 0.0f)
				{
					l_fRotationZ = -l_fRotationZ;
				}
			}
			else if (l_fHorizontalVelocity == 0.0f)
			{
				l_fRotationZ = l_fVerticalVelocity > 0.0f ? M_PI_2 : -M_PI_2;
			}
			else if (l_fVerticalVelocity == 0.0f)
			{
				l_fRotationZ = l_fHorizontalVelocity > 0.0f ? 0.0f : M_PI;
			}

			float l_fDotMovementToFace = glm::dot(l_v2PlayerToMouseDirection, glm::normalize(glm::vec2{ l_fHorizontalVelocity , l_fVerticalVelocity }));
			// If movement is opposite direction fo cursor face, the rotate legs by 180 so shoes are always pointing to cursor face.
			if (l_fDotMovementToFace < -0.5)
			{
				l_fRotationZ += M_PI;
			}
			m_pGameObjCharacterLegs->m_Transform.setLocalRotation({ 0.0f, 0.0f, l_fRotationZ});
		}

		m_pUpperSpriteAnimator->play(l_strPlayerAnimTrigger);
		m_pLegsSpriteAnimator->play(l_strPlayerAnimTrigger);
		m_pRectCollider->setLinearVelocity({ l_fHorizontalVelocity, l_fVerticalVelocity });
		m_pCamGameObj->m_Transform.setWorldPosition(m_GameObject.m_Transform.getWorldPosition());


		//// DEBUG START //// 
		if (ns_fretBuzz::ns_system::Input::IsKeyPutDown(GLFW_KEY_L))
		{
			ns_fretBuzz::ns_system::SceneManager::LogSceneHierarchy();
		}
		//// DEBUG END ////

		if (ns_fretBuzz::ns_system::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_1))
		{
			m_pUpperSpriteAnimator->play("attack");
			/*ns_fretBuzz::ns_system::Collider2D* l_pCollider2D = nullptr;
			glm::vec2 l_v2PlayerPosition = m_GameObject.m_Transform.getWorldPosition();
			glm::vec2 l_v2MouseWorldPosition = l_v2PlayerPosition + l_MousePosition;

			ns_fretBuzz::ns_system::PhysicsEngine::Raycast(l_pCollider2D, l_v2PlayerPosition, l_v2MouseWorldPosition);

			if (l_pCollider2D != nullptr)
			{
				InteractiveObject* l_pInteractiveObject = l_pCollider2D->m_GameObject.getComponent<InteractiveObject>(ns_fretBuzz::ns_system::COMPONENT_TYPE::BEHAVIOUR);
				if (l_pInteractiveObject != nullptr)
				{
					l_pInteractiveObject->onLabelHit();
				}
			}*/
		}
		else if (ns_fretBuzz::ns_system::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_2))
		{
			//m_pUpperSpriteAnimator->play("humanshield");
			if (m_pPlayerOverWeapon != nullptr)
			{
				m_pUpperSpriteAnimator->play("magnumidle");
				m_pPlayerOverWeapon->m_GameObject.setActive(false);
			}
		}
		else if (ns_fretBuzz::ns_system::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_3))
		{
			m_pUpperSpriteAnimator->play("snap");
		}
	}

	void PlayerController::onCollisionEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent)
	{
		std::cout << "PlayerController::OnCollisionEnter2D:: " << a_pIComponent->m_GameObject.getName() << "\n";
	}

	void PlayerController::onCollisionExit2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent)
	{
		std::cout << "PlayerController::OnCollisionExit2D:: " << a_pIComponent->m_GameObject.getName() << "\n";
	}

	void PlayerController::onTriggerEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent)
	{
		std::cout << "PlayerController::OnTriggerEnter2D:: " << a_pIComponent->m_GameObject.getName() << "\n";
	}

	void PlayerController::onTriggerExit2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent)
	{
		std::cout << "PlayerController::OnTriggerExit2D:: " << a_pIComponent->m_GameObject.getName() << "\n";
	}

	void PlayerController::setAsCurrentWeapon(ns_HMGame::Weapon* a_pWeapon)
	{
		m_iWeaponOverCount = a_pWeapon == nullptr ? --m_iWeaponOverCount : ++m_iWeaponOverCount;

		if (a_pWeapon != nullptr)
		{
			m_pPlayerOverWeapon = a_pWeapon;
		}
		else if (m_iWeaponOverCount == 0)
		{
			m_pPlayerOverWeapon = nullptr;
		}
	}
}