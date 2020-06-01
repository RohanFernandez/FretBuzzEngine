#pragma once
#include <components/gameobject_components/behaviour.h>
#include "components/gameobject_components/sprite_animation_controller.h"

namespace ns_HMGame
{
	class CursorManager : public ns_fretBuzz::ns_system::Behaviour
	{
	private:
		double m_dMouseX = 0.0;
		double m_dMouseY = 0.0;

		ns_fretBuzz::ns_system::SpriteAnimationController* m_pSpriteAnimator = nullptr;
		ns_fretBuzz::ns_graphics::Camera* m_pCamComponent = nullptr;

	public:
		CursorManager(ns_fretBuzz::ns_system::GameObject* a_GameObject, ns_fretBuzz::ns_graphics::Camera* a_pCamComponent);
		virtual void update(const float& a_fDeltaTime) override;
	};
}