#pragma once

#include "../framework/system/game_object.h" 
#include "../framework/components/gameobject_components/audio_source.h"
#include "../framework/components/gameobject_components/sprite_animation_controller.h"

#include "../framework/graphics/shader.h"
#include "../framework/graphics/texture.h"
#include "../framework/components/camera.h"
#include "../framework/system/core/input.h"

namespace ns_fretBuzz
{
	class CharacterTest : public ns_system::GameObject
	{
	private:
		ns_system::AudioSource* m_pAudSrc = nullptr;
		ns_system::SpriteAnimationController* m_pSpriteAnimator = nullptr;

		bool isAudioPlaying = false;

		double m_dMouseX = 0.0;
		double m_dMouseY = 0.0;

		float m_fVelocity = 200.0f;

		float m_fScale = 1.0f;
		float m_fScaleVelocity = 2.0f;

	public:

		CharacterTest(GameObject& a_ParentGameObject, std::string a_strName);

		virtual void update(float a_fDeltaTime) override;
		virtual void render(const glm::mat4& a_mat4Transformation, const ns_system::Camera& a_Camera) override;
	};
}