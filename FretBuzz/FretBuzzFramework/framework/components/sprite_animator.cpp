#include <fretbuzz_pch.h>
#include "sprite_animator.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		void SpriteAnimator::destroyResource()
		{
		
		}

		SpriteAnimator::SpriteAnimator(std::string a_strAnimControllerId, std::vector<AnimationState> a_vectAnimStates)
			: IManagedResource(), 
			m_strAnimControllerId(a_strAnimControllerId),
			m_vectAnimationStates(a_vectAnimStates)
		{
		
		}

		SpriteAnimator::SpriteAnimator(SpriteAnimator& a_SpriteAnimationController)
			: SpriteAnimator(a_SpriteAnimationController.m_strAnimControllerId, a_SpriteAnimationController.m_vectAnimationStates)
		{

		}

		SpriteAnimator::SpriteAnimator(SpriteAnimator&& a_SpriteAnimationController)
			: SpriteAnimator(a_SpriteAnimationController)
		{
		
		}

		void SpriteAnimator::operator=(SpriteAnimator a_SpriteAnimationController)
		{
			m_strAnimControllerId = a_SpriteAnimationController.m_strAnimControllerId;
			m_vectAnimationStates = a_SpriteAnimationController.m_vectAnimationStates;
		}

		SpriteAnimator:: ~SpriteAnimator()
		{

		}

		AnimationState* SpriteAnimator::getAnimStateWithID(std::string a_strAnimStateID)
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