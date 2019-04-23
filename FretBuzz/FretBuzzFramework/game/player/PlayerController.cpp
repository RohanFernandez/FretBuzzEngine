#include <fretbuzz_pch.h>
#include "PlayerController.h"
#include <system/core/input.h>

namespace ns_HMGame
{
	PlayerController::PlayerController(ns_fretBuzz::ns_system::GameObject& a_GameObject, ns_fretBuzz::ns_system::GameObject* a_pCamGameObject, ns_fretBuzz::ns_system::GameObject* a_pLegsGameObject)
		: ns_fretBuzz::ns_system::Behaviour(a_GameObject)
	{
		m_pSpriteAnimator = a_GameObject.getComponent<ns_fretBuzz::ns_system::SpriteAnimationController>(ns_fretBuzz::ns_system::COMPONENT_TYPE::SPRITE_ANIMATION_CONTROLLER);
		m_pRectCollider = a_GameObject.getComponent<ns_fretBuzz::ns_system::RectCollider>(ns_fretBuzz::ns_system::COMPONENT_TYPE::RECT_COLLIDER);
		m_pCamGameObj = a_pCamGameObject;

		m_pGameObjCharacterLegs = a_pLegsGameObject;
		m_pLegsSpriteAnimator = a_pLegsGameObject->getComponent<ns_fretBuzz::ns_system::SpriteAnimationController >(ns_fretBuzz::ns_system::COMPONENT_TYPE::SPRITE_ANIMATION_CONTROLLER);
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
			m_pSpriteAnimator->play("attack");
		}
		else if (ns_fretBuzz::ns_system::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_2))
		{
			m_pSpriteAnimator->play("humanshield");
		}
		else if (ns_fretBuzz::ns_system::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_3))
		{
			m_pSpriteAnimator->play("snap");
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

		if (l_fHorizontalVelocity != 0.0f &&
			l_fVerticalVelocity != 0.0f)
		{
			l_fHorizontalVelocity *= 0.7f;
			l_fVerticalVelocity *= 0.7f;
			
		}

		if (l_fHorizontalVelocity != 0.0f || l_fVerticalVelocity != 0.0f)
		{
			if (!m_bIsRunning)
			{
				m_pLegsSpriteAnimator->play("walk");
			}
			m_bIsRunning = true;
		}
		else
		{
			if (m_bIsRunning)
			{
				m_pLegsSpriteAnimator->play("idle");
			}
			m_bIsRunning = false;
		}


		m_pRectCollider->setLinearVelocity({ l_fHorizontalVelocity, l_fVerticalVelocity });
		m_pCamGameObj->m_Transform.setWorldPosition(m_GameObject.m_Transform.getWorldPosition());

		ns_fretBuzz::ns_system::Input::GetMousePosition(m_dMouseX, m_dMouseY);

		glm::vec3 l_MousePosition = glm::vec3((float)m_dMouseX - (ns_fretBuzz::ns_graphics::Window::getWidth() * 0.5f), (ns_fretBuzz::ns_graphics::Window::getHeight() * 0.5f) - (float)m_dMouseY, 0.0f);
		glm::vec3 l_v3PlayerPosition = m_GameObject.m_Transform.getLocalPosition();

		glm::vec3 l_v3PlayerToMouseDirection = glm::normalize(l_MousePosition);

		float a_fZ = glm::atan(l_v3PlayerToMouseDirection.x, l_v3PlayerToMouseDirection.y);
		m_GameObject.m_Transform.setLocalRotation({ 0.0f, 0.0f, -a_fZ + M_PI_2 });
	}
}