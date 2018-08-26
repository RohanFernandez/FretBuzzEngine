#pragma once
#include "sprite_animation_controller.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		void SpriteAnimationController::destroyResource()
		{
		
		}

		SpriteAnimationController::SpriteAnimationController(std::string a_strAnimControllerId, std::vector<AnimationState> a_vectAnimStates)
			: IManagedResource(), 
			m_strAnimControllerId(a_strAnimControllerId),
			m_vectAnimationStates(a_vectAnimStates)
		{
		
		}

		SpriteAnimationController::SpriteAnimationController(SpriteAnimationController& a_SpriteAnimationController)
			: SpriteAnimationController(a_SpriteAnimationController.m_strAnimControllerId, a_SpriteAnimationController.m_vectAnimationStates)
		{

		}

		SpriteAnimationController::SpriteAnimationController(SpriteAnimationController&& a_SpriteAnimationController)
			: SpriteAnimationController(a_SpriteAnimationController)
		{
		
		}

		void SpriteAnimationController::operator=(SpriteAnimationController a_SpriteAnimationController)
		{
			m_strAnimControllerId = a_SpriteAnimationController.m_strAnimControllerId;
			m_vectAnimationStates = a_SpriteAnimationController.m_vectAnimationStates;
		}

		SpriteAnimationController:: ~SpriteAnimationController()
		{

		}

		AnimationState* SpriteAnimationController::getAnimStateWithID(std::string a_strAnimStateID)
		{
			for (auto l_Iterator = m_vectAnimationStates.begin(), l_IteratorEnd = m_vectAnimationStates.end();
				l_Iterator != l_IteratorEnd; l_Iterator++)
			{
				if (l_Iterator->getStateId().compare(a_strAnimStateID) == 0)
				{
					return &(*l_Iterator);
				}
			}

			return nullptr;
		}
	}
}