#pragma once

#include "system/game_object_2d.h" 
#include "components/gameobject_components/audio_source.h"
#include "components/gameobject_components/sprite_animation_controller.h"
#include "components/gameobject_components/rect_collider.h"

#include "graphics/shader.h"
#include "graphics/texture.h"
#include "components/viewport.h"
#include "system/core/input.h"

namespace ns_HMGame
{
	class CharacterTest : public ns_fretBuzz::ns_system::GameObject2D
	{
	private:
		ns_fretBuzz::ns_system::AudioSource* m_pAudSrc = nullptr;
		ns_fretBuzz::ns_system::SpriteAnimationController* m_pSpriteAnimator = nullptr;
		ns_fretBuzz::ns_system::RectCollider* m_pRectCollider = nullptr;

		ns_fretBuzz::ns_system::GameObject* m_pcamGameObj = nullptr;

		bool isAudioPlaying = false;

		double m_dMouseX = 0.0;
		double m_dMouseY = 0.0;

		float m_fVelocity = 250.0f;

		float m_fScale = 1.0f;
		float m_fScaleVelocity = 2.0f;

		int m_iCurrentWeaponID = 0;
		GameObject* m_pRefOriginGameObject = nullptr;


	public:

		ns_fretBuzz::ns_system::GameObject* m_pTestGameObject1 = nullptr;
		ns_fretBuzz::ns_system::GameObject* m_pTestGameObject2 = nullptr;

		CharacterTest(GameObject& a_ParentGameObject, std::string a_strName, ns_fretBuzz::ns_system::GameObject* a_CamGameObject, GameObject& a_refOriginGameObject);

		virtual void update(const float& a_fDeltaTime) override;
		virtual void render(const ns_fretBuzz::ns_graphics::Camera& a_Camera) override;
	};
}