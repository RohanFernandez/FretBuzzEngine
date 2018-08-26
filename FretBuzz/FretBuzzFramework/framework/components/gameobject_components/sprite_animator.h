#pragma once
#include "../sprite_animation_controller.h"
#include "sprite_renderer.h"
#include <map>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class SpriteAnimator : public IComponent
		{
		private:
			SpriteAnimator(GameObject& a_GameObj, std::string a_strAnimationControllerId);
			~SpriteAnimator();

			SpriteAnimationController* m_pSpriteAnimationController = nullptr;

			ns_graphics::Sprite* m_pCurrentSprite = nullptr;
			ns_graphics::SpriteRenderer* m_pSpriteRenderer = nullptr;
			std::vector<ns_graphics::Sprite>* m_pCurrentSpriteSheet = nullptr;

			AnimationState* m_pAnimState = nullptr;

			bool m_bIsCurrentAnimationLooped = false;
			int m_iSpriteCount = 0;
			float m_fTimePassedInCurrentSprite = 0.0f;
			float m_fTimePerSprite = 0.0f;
			int m_iCurrentSpriteIndex = 0;

			std::string m_strDefaultStateID;

			void playStateID(std::string a_strAnimationID);

			static constexpr COMPONENT_TYPE s_COMPONENT_TYPE = COMPONENT_TYPE::SPRITE_ANIMATOR;

		public:
			static SpriteAnimator* addToGameObject(GameObject& a_GameObj, std::string a_strAnimationControllerId);

			void play(std::string a_strAnimationID);
			void pause();

			virtual void update(float a_fDeltaTime) override;
			virtual void render(const glm::mat4& a_mat4Transformation, const Camera& a_Camera) override;
		};
	}
}