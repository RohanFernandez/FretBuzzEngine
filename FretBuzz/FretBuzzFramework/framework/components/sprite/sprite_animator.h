#pragma once
#include "sprite_renderer.h"
#include <map>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class SpriteAnimator : public IComponent
		{
		private:
			std::map<std::string, ns_graphics::SpriteSheet*> m_mapSpriteSheetIDs;
			SpriteAnimator(GameObject& a_GameObj, std::vector<std::string> a_vectSpriteSheedIDs);
			~SpriteAnimator();

			std::vector<ns_graphics::Sprite>* m_pCurrentSpriteSheet = nullptr;
			ns_graphics::Sprite* m_pCurrentSprite = nullptr;
			ns_graphics::SpriteRenderer* m_pSpriteRenderer = nullptr;

			int m_iSpriteCount = 0;

			float m_fTimePassedInCurrentSprite = 0.0f;
			float m_fTimePerSprite = 0.0f;
			int m_iCurrentSpriteIndex = 0;

			static constexpr COMPONENT_TYPE s_COMPONENT_TYPE = COMPONENT_TYPE::SPRITE_ANIMATOR;

		public:
			static SpriteAnimator* addToGameObject(GameObject& a_GameObj, std::vector<std::string> a_vectSpriteSheedIDs);

			void play(std::string a_strAnimationID, bool a_bIsLooped = false);
			void pause();

			virtual void update(float a_fDeltaTime) override;
			virtual void render(const glm::mat4& a_mat4Transformation, const Camera& a_Camera) override;
		};
	}
}