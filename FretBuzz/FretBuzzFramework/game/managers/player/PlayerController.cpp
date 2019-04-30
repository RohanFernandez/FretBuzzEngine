#include <fretbuzz_pch.h>
#include "PlayerController.h"
#include <system/core/input.h>
#include <system/scene_manager.h>

namespace ns_HMGame
{
	PlayerController::PlayerController(ns_fretBuzz::ns_system::GameObject& a_GameObject, ns_fretBuzz::ns_system::GameObject* a_pCamGameObject, ns_fretBuzz::ns_system::GameObject* a_pPlayerUpperGameObj, ns_fretBuzz::ns_system::GameObject* a_pLegsGameObject)
		: ns_fretBuzz::ns_system::Behaviour(a_GameObject),
		ns_fretBuzz::ns_system::CollisionEvents2D()
	{
		m_pPlayerUpperGameObj = a_pPlayerUpperGameObj;
		m_pGameObjCharacterLegs = a_pLegsGameObject;

		m_pRectCollider = a_GameObject.getComponent<ns_fretBuzz::ns_system::RectCollider>(ns_fretBuzz::ns_system::COMPONENT_TYPE::RECT_COLLIDER);
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
		if (ns_fretBuzz::ns_system::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_1))
		{
			m_pUpperSpriteAnimator->play("attack");
		}
		else if (ns_fretBuzz::ns_system::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_2))
		{
			m_pUpperSpriteAnimator->play("humanshield");
		}
		else if (ns_fretBuzz::ns_system::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_3))
		{
			m_pUpperSpriteAnimator->play("snap");
		}

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
	}
}