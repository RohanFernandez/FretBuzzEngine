#pragma once
#include <components/gameobject_components/behaviour.h>
#include "components/gameobject_components/sprite_animation_controller.h"
#include <components/gameobject_components/rect_collider.h>

namespace ns_HMGame
{
	class PlayerController : public ns_fretBuzz::ns_system::Behaviour
	{
	private:
		double m_dMouseX = 0.0;
		double m_dMouseY = 0.0;

		float m_fVelocity = 250.0f;

		ns_fretBuzz::ns_system::SpriteAnimationController* m_pSpriteAnimator = nullptr;
		ns_fretBuzz::ns_system::RectCollider* m_pRectCollider = nullptr;

		ns_fretBuzz::ns_system::GameObject* m_pCamGameObj = nullptr;

		void manageInput();
	public:
		PlayerController(ns_fretBuzz::ns_system::GameObject& a_GameObject, ns_fretBuzz::ns_system::GameObject* a_pCamGameObject);

		virtual void update(float a_fDeltaTime) override;
	};
}