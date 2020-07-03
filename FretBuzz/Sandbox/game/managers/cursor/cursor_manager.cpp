#include "fretbuzz_pch.h"
#include "cursor_manager.h"
#include <input.h>

namespace ns_HMGame
{
	CursorManager::CursorManager(ns_fretBuzz::GameObject* a_GameObject, ns_fretBuzz::Camera* a_CameraComponent)
		: ns_fretBuzz::Behaviour(a_GameObject)
	{
		m_pSpriteAnimator = a_GameObject->getComponent<ns_fretBuzz::SpriteAnimationController>(ns_fretBuzz::COMPONENT_TYPE::SPRITE_ANIMATION_CONTROLLER);
		m_pCamComponent = a_CameraComponent;
	}

	void CursorManager::update(const float& a_fDeltaTime)
	{
		ns_fretBuzz::Input::GetMousePosition(m_dMouseX, m_dMouseY);

		glm::vec3 l_MousePosition = glm::vec3((float)m_dMouseX - (ns_fretBuzz::Window::getWidth() * 0.5f), (ns_fretBuzz::Window::getHeight() * 0.5f) - (float)m_dMouseY, 0.0f) + m_pCamComponent->m_GameObject.m_Transform.getWorldPosition();
		m_GameObject.m_Transform.setWorldPosition(l_MousePosition);
		Behaviour::update(a_fDeltaTime);
	}
}
