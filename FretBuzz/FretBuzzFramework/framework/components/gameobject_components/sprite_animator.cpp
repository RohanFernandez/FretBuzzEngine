#pragma once
#include "sprite_animator.h"
#include "../../system/core/resource_manager.h"
#include "../../system/game_object.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		SpriteAnimator::SpriteAnimator(GameObject& a_GameObj, std::string a_strAnimationControllerId)
			: IComponent(s_COMPONENT_TYPE, a_GameObj)
		{
			m_pSpriteRenderer = m_GameObject.getComponent<ns_graphics::SpriteRenderer>(COMPONENT_TYPE::SPRITE_RENDERER);
			if (m_pSpriteRenderer == nullptr)
			{
				m_pSpriteRenderer = ns_graphics::SpriteRenderer::addToGameObject(m_GameObject, nullptr);
			}

			m_pSpriteAnimationController = ResourceManager::getResource<SpriteAnimationController>(a_strAnimationControllerId);
			if (m_pSpriteAnimationController == nullptr)
			{
				std::cout << "SpriteAnimator::SpriteAnimator:: Sprite anim controller with id '"<< a_strAnimationControllerId <<"' does not exist as a resource\n";
				return;
			}

			m_strDefaultStateID = m_pSpriteAnimationController->getAnimStates()[0].getStateId();
			m_pAnimState = m_pSpriteAnimationController->getAnimStateWithID(m_strDefaultStateID);


			/*std::map<std::string, ns_graphics::SpriteSheet*>::iterator l_iterator = m_mapSpriteSheetIDs.begin();

			int l_iSpriteSheetCount = a_vectSpriteSheetIDs.size();
			for (int l_iSpriteSheetIndex = 0; l_iSpriteSheetIndex < l_iSpriteSheetCount; l_iSpriteSheetIndex++)
			{
				std::string l_strSpriteSheetIndex = a_vectSpriteSheetIDs[l_iSpriteSheetIndex];
				m_mapSpriteSheetIDs.insert(l_iterator, std::pair<std::string, ns_graphics::SpriteSheet*>(l_strSpriteSheetIndex, ResourceManager::getResource<ns_graphics::SpriteSheet>(l_strSpriteSheetIndex)));
			}*/
		}

		SpriteAnimator::~SpriteAnimator()
		{
			
		}

		SpriteAnimator* SpriteAnimator::addToGameObject(GameObject& a_GameObj, std::string a_strAnimationControllerId)
		{
			return new SpriteAnimator(a_GameObj, a_strAnimationControllerId);
		}

		void SpriteAnimator::play(std::string a_strTrigger)
		{
			std::map<std::string, std::string> l_MapTriggers = m_pAnimState->getMapTriggers();
			std::map<std::string, std::string>::iterator l_SpriteSheetIterator = l_MapTriggers.find(a_strTrigger);
			if (l_SpriteSheetIterator == l_MapTriggers.end())
			{
				std::cout << "SpriteAnimator::play::: Could not find sprite sheet id '"<< a_strTrigger <<"'\n";
				return;
			}

			playStateID(l_SpriteSheetIterator->second);
		}

		void SpriteAnimator::playStateID(std::string a_strAnimationID)
		{
			m_pAnimState = m_pSpriteAnimationController->getAnimStateWithID(a_strAnimationID);
			m_pCurrentSpriteSheet = m_pAnimState->getSpriteSheet()->getSprites();
			m_iCurrentSpriteIndex = 0;
			m_pCurrentSprite = &(*m_pCurrentSpriteSheet)[m_iCurrentSpriteIndex];

			m_fTimePassedInCurrentSprite = 0.0f;
			m_fTimePerSprite = m_pAnimState->getTimePerSprite();
			m_bIsCurrentAnimationLooped = m_pAnimState->isLooped();
			m_iSpriteCount = m_pAnimState->getSpriteSheet()->getSpriteCount();

		}

		void SpriteAnimator::update(float a_fDeltaTime)
		{
			if (m_pCurrentSprite == nullptr) { return; }
			m_fTimePassedInCurrentSprite += a_fDeltaTime;

			if (m_fTimePassedInCurrentSprite >= m_fTimePerSprite)
			{
				m_fTimePassedInCurrentSprite -= m_fTimePerSprite;

				if (!m_bIsCurrentAnimationLooped && m_iCurrentSpriteIndex == (m_iSpriteCount - 1))
				{
 					playStateID(m_strDefaultStateID);
					return;
				}

				m_pCurrentSprite = &(*m_pCurrentSpriteSheet)[(++m_iCurrentSpriteIndex) % m_iSpriteCount];
				m_pSpriteRenderer->setSprite(m_pCurrentSprite);
			}
		}

		void SpriteAnimator::render(const glm::mat4& a_mat4Transformation, const Camera& a_Camera)
		{

		}
	}
}