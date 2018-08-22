#pragma once
#include "sprite_animator.h"
#include "../../system/resource_manager.h"
#include "../../game/game_object.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		SpriteAnimator::SpriteAnimator(GameObject& a_GameObj, std::vector<std::string> a_vectSpriteSheetIDs)
			: IComponent(s_COMPONENT_TYPE, a_GameObj)
		{
			m_pSpriteRenderer = m_GameObject.getComponent<ns_graphics::SpriteRenderer>(COMPONENT_TYPE::SPRITE_RENDERER);

			std::map<std::string, ns_graphics::SpriteSheet*>::iterator l_iterator = m_mapSpriteSheetIDs.begin();

			int l_iSpriteSheetCount = a_vectSpriteSheetIDs.size();
			for (int l_iSpriteSheetIndex = 0; l_iSpriteSheetIndex < l_iSpriteSheetCount; l_iSpriteSheetIndex++)
			{
				std::string l_strSpriteSheetIndex = a_vectSpriteSheetIDs[l_iSpriteSheetIndex];
				m_mapSpriteSheetIDs.insert(l_iterator, std::pair<std::string, ns_graphics::SpriteSheet*>(l_strSpriteSheetIndex, ResourceManager::getResource<ns_graphics::SpriteSheet>(l_strSpriteSheetIndex)));
			}
		}

		SpriteAnimator::~SpriteAnimator()
		{
			
		}

		SpriteAnimator* SpriteAnimator::addToGameObject(GameObject& a_GameObj, std::vector<std::string> a_vectSpriteSheedIDs)
		{
			return new SpriteAnimator(a_GameObj, a_vectSpriteSheedIDs);
		}

		void SpriteAnimator::play(std::string a_strAnimationID)
		{
			std::map<std::string, ns_graphics::SpriteSheet*>::iterator l_SpriteSheetIterator = m_mapSpriteSheetIDs.find(a_strAnimationID);
			if (l_SpriteSheetIterator == m_mapSpriteSheetIDs.end())
			{
				std::cout << "SpriteAnimator::play::: Could not find sprite sheet id '"<< a_strAnimationID <<"'\n";
				return;
			}

			m_pCurrentSpriteSheet = l_SpriteSheetIterator->second->getSpriteSheet();
			m_fTimePerSprite = l_SpriteSheetIterator->second->getTimePerSprite();
			m_fTimePassedInCurrentSprite = 0;

			m_iSpriteCount = m_pCurrentSpriteSheet->size();
			m_iCurrentSpriteIndex = 0;
			m_pCurrentSprite = &(*m_pCurrentSpriteSheet)[m_iCurrentSpriteIndex];
			m_pSpriteRenderer->setSprite(m_pCurrentSprite);
		}

		void SpriteAnimator::update(float a_fDeltaTime)
		{
			if (m_pCurrentSprite == nullptr) { return; }
			m_fTimePassedInCurrentSprite += a_fDeltaTime;

			if (m_fTimePassedInCurrentSprite >= m_fTimePerSprite)
			{
				m_fTimePassedInCurrentSprite -= m_fTimePerSprite;
				m_pCurrentSprite = &(*m_pCurrentSpriteSheet)[(++m_iCurrentSpriteIndex) % m_iSpriteCount];
				m_pSpriteRenderer->setSprite(m_pCurrentSprite);
			}
		}

		void SpriteAnimator::render(const Camera& a_Camera)
		{

		}
	}
}