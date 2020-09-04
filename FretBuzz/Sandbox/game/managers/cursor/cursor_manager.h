#pragma once
#include <components/gameobject_components/behaviour.h>
#include "components/gameobject_components/sprite_animation_controller.h"

namespace ns_HMGame
{
	class CursorManager : public FRETBUZZ::Behaviour
	{
	private:
		double m_dMouseX = 0.0;
		double m_dMouseY = 0.0;

		FRETBUZZ::SpriteAnimationController* m_pSpriteAnimator = nullptr;
		FRETBUZZ::Camera* m_pCamComponent = nullptr;

	public:
		CursorManager(FRETBUZZ::GameObject* a_GameObject, FRETBUZZ::Camera* a_pCamComponent);
		virtual void update(const float& a_fDeltaTime) override;
	};
}