#include <fretbuzz_pch.h>
#include "sprite_animation_controller.h"
#include "system/core/resource_manager.h"
#include "system/game_object.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		SpriteAnimationController::SpriteAnimationController(GameObject* a_GameObj, std::string a_strAnimatorId)
			: IComponent(COMPONENT_TYPE::SPRITE_ANIMATION_CONTROLLER, a_GameObj)
		{
			m_pSpriteRenderer = m_GameObject.getComponent<ns_graphics::SpriteRenderer>(COMPONENT_TYPE::SPRITE_RENDERER);
			if (m_pSpriteRenderer == nullptr)
			{
				m_pSpriteRenderer = m_GameObject.addComponent<ns_graphics::SpriteRenderer>(nullptr);
			}

			m_pSpriteAnimator = ResourceManager::getResource<SpriteAnimator>(a_strAnimatorId);
			if (m_pSpriteAnimator == nullptr)
			{
				ENGINE_WARN("SpriteAnimationController::SpriteAnimationController:: Sprite anim controller with id {0} does not exist as a resource", a_strAnimatorId);
				return;
			}

			m_strDefaultStateID = m_pSpriteAnimator->getAnimStates()[0].getStateId();
			m_pAnimState = m_pSpriteAnimator->getAnimStateWithID(m_strDefaultStateID);
			playStateID(m_strDefaultStateID);
		}

		SpriteAnimationController::~SpriteAnimationController()
		{
			
		}

		void SpriteAnimationController::play(std::string a_strTrigger)
		{
			std::map<std::string, std::string> l_MapTriggers = m_pAnimState->getMapTriggers();
			std::map<std::string, std::string>::iterator l_SpriteSheetIterator = l_MapTriggers.find(a_strTrigger);
			if (l_SpriteSheetIterator != l_MapTriggers.end())
			{
				playStateID(l_SpriteSheetIterator->second);
			}

		}

		void SpriteAnimationController::playStateID(std::string a_strAnimationID)
		{
			m_pAnimState = m_pSpriteAnimator->getAnimStateWithID(a_strAnimationID);
			ns_graphics::SpriteGroup* l_pCurrentSpriteGroup = ResourceManager::getResource<ns_graphics::SpriteGroup>(m_pAnimState->getSpriteGroupID());
			m_pCurrentSpriteSheet = l_pCurrentSpriteGroup->getSprites();
			m_iCurrentSpriteIndex = 0;
			m_pCurrentSprite = &(*m_pCurrentSpriteSheet)[m_iCurrentSpriteIndex];
			m_pSpriteRenderer->setSprite(m_pCurrentSprite);

			m_fTimePassedInCurrentSprite = 0.0f;
			m_fTimePerSprite = m_pAnimState->getTimePerSprite();
			m_bIsCurrentAnimationLooped = m_pAnimState->isLooped();
			m_iSpriteCount = l_pCurrentSpriteGroup->getSpriteCount();

			std::string l_strOnCompleteTrigger = m_pAnimState->getOnCompleteTrigger();
			m_strCurrentonCompleteTrigger = ((l_strOnCompleteTrigger.compare("") == 0) ? m_strDefaultStateID : l_strOnCompleteTrigger);
		}

		void SpriteAnimationController::update(const float& a_fDeltaTime)
		{
			if (m_pCurrentSprite == nullptr) { return; }
			m_fTimePassedInCurrentSprite += a_fDeltaTime;

			if (m_fTimePassedInCurrentSprite >= m_fTimePerSprite)
			{
				m_fTimePassedInCurrentSprite -= m_fTimePerSprite;

				++m_iCurrentSpriteIndex;
				if (!m_bIsCurrentAnimationLooped && m_iCurrentSpriteIndex >= m_iSpriteCount)
				{
 					play(m_strCurrentonCompleteTrigger);
					return;
				}

				m_pCurrentSprite = &(*m_pCurrentSpriteSheet)[m_iCurrentSpriteIndex % m_iSpriteCount];
				m_pSpriteRenderer->setSprite(m_pCurrentSprite);
			}
		}
	}
}