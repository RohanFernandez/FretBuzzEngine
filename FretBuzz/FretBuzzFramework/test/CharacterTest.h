#pragma once

#include "../framework/system/game_object_2d.h" 
#include "../framework/components/gameobject_components/audio_source.h"
#include "../framework/components/gameobject_components/sprite_animation_controller.h"
#include "../framework/components/gameobject_components/rect_collider.h"

#include "../framework/graphics/shader.h"
#include "../framework/graphics/texture.h"
#include "../framework/components/viewport.h"
#include "../framework/system/core/input.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace ns_fretBuzz
{
	class CharacterTest : public ns_system::GameObject2D
	{
	private:
		ns_system::AudioSource* m_pAudSrc = nullptr;
		ns_system::SpriteAnimationController* m_pSpriteAnimator = nullptr;
		ns_system::RectCollider* m_pRectCollider = nullptr;

		ns_system::GameObject* m_pcamGameObj = nullptr;

		bool isAudioPlaying = false;

		double m_dMouseX = 0.0;
		double m_dMouseY = 0.0;

		float m_fVelocity = 250.0f;

		float m_fScale = 1.0f;
		float m_fScaleVelocity = 2.0f;

		Assimp::Importer importer;

	public:

		ns_system::GameObject* m_pTestGameObject1 = nullptr;
		ns_system::GameObject* m_pTestGameObject2 = nullptr;

		CharacterTest(GameObject& a_ParentGameObject, std::string a_strName, ns_system::GameObject* a_CamGameObject);

		virtual void update(float a_fDeltaTime) override;
		virtual void render(const ns_system::Camera& a_Camera) override;
	};
}