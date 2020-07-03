#pragma once
#include <components/gameobject_components/behaviour.h>
#include "components/gameobject_components/sprite_animation_controller.h"

namespace ns_HMGame
{
	class CursorManager : public ns_fretBuzz::Behaviour
	{
	private:
		double m_dMouseX = 0.0;
		double m_dMouseY = 0.0;

		ns_fretBuzz::SpriteAnimationController* m_pSpriteAnimator = nullptr;
		ns_fretBuzz::Camera* m_pCamComponent = nullptr;

	public:
		CursorManager(ns_fretBuzz::GameObject* a_GameObject, ns_fretBuzz::Camera* a_pCamComponent);
		virtual void update(const float& a_fDeltaTime) override;
	};
}