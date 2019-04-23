#pragma once

#include "system/game_object_2d.h" 
#include "components/gameobject_components/sprite_animation_controller.h"
#include "components/gameobject_components/rect_collider.h"

namespace ns_fretBuzz
{
	class FRETBUZZ_API EnemyTest : public ns_system::GameObject2D
	{
	private:
		ns_system::SpriteAnimationController* m_pSpriteAnimator = nullptr;

		ns_system::RectCollider* m_pRectCollider = nullptr;

	public:
		EnemyTest(GameObject& a_ParentGameObject, std::string a_strName);

		//virtual void update(float a_fDeltaTime) override;
		//virtual void render(const ns_graphics::Camera& a_Camera) override;
	};
}