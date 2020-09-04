#pragma once

#include "system/game_object_2d.h" 
#include "components/gameobject_components/sprite_animation_controller.h"
#include "components/gameobject_components/rect_collider.h"

namespace ns_HMGame
{
	class EnemyTest : public FRETBUZZ::GameObject2D
	{
	private:
		FRETBUZZ::SpriteAnimationController* m_pSpriteAnimator = nullptr;

		FRETBUZZ::RectCollider* m_pRectCollider = nullptr;

	public:
		EnemyTest(GameObject& a_ParentGameObject, std::string a_strName);

		//virtual void update(float a_fDeltaTime) override;
		//virtual void render(const Camera& a_Camera) override;
	};
}