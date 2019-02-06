#pragma once
#include "../sprite_animator.h"
#include "sprite_renderer.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class FRETBUZZ_API SpriteAnimationController : public IComponent
		{
		private:
			SpriteAnimationController(GameObject& a_GameObj, std::string a_strAnimatorId);

			SpriteAnimator* m_pSpriteAnimator = nullptr;

			ns_graphics::Sprite* m_pCurrentSprite = nullptr;
			ns_graphics::SpriteRenderer* m_pSpriteRenderer = nullptr;
			std::vector<ns_graphics::Sprite>* m_pCurrentSpriteSheet = nullptr;

			AnimationState* m_pAnimState = nullptr;

			bool m_bIsCurrentAnimationLooped = false;
			int m_iSpriteCount = 0;
			float m_fTimePassedInCurrentSprite = 0.0f;
			float m_fTimePerSprite = 0.0f;
			int m_iCurrentSpriteIndex = 0;

			std::string m_strCurrentonCompleteTrigger;

			std::string m_strDefaultStateID;

			void playStateID(std::string a_strAnimationID);

		protected:
			~SpriteAnimationController();

		public:
			static SpriteAnimationController* addToGameObject(GameObject& a_GameObj, std::string a_strAnimationControllerId);

			void play(std::string a_strAnimationID);

			virtual void update(float a_fDeltaTime) override;
		};
	}
}