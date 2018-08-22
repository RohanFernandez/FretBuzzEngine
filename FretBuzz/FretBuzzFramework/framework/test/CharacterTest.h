#pragma once

#include "../game/game_object.h" 
#include "../components/audio/audio_source.h"
#include "../components/sprite/sprite_animator.h"

#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../components/camera/camera.h"
#include "../system/input.h"

#include "../components/camera/camera.h"

namespace ns_fretBuzz
{
	class CharacterTest : public ns_system::GameObject
	{
	private:
		ns_system::AudioSource* m_pAudSrc = nullptr;
		ns_system::SpriteAnimator* m_pSpriteAnimator = nullptr;

		ns_graphics::Shader* m_pShader = nullptr;
		ns_graphics::Texture* m_pTexture = nullptr;

		bool isAudioPlaying = false;

	public:

		CharacterTest();
		virtual ~CharacterTest() {};

		virtual void update(float a_fDeltaTime) override;
		virtual void render(const ns_system::Camera& a_Camera) override;
	};
}