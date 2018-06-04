#pragma once
#include "update_manager.h"

namespace ns_fretBuzz
{
	namespace ns_manager
	{
			//singleton instance
			UpdateManager* UpdateManager::s_pInstance = nullptr;

			UpdateManager::UpdateManager()
			{
				if (s_pInstance == nullptr)
				{
					s_pInstance = this;
				}
			}

			UpdateManager::~UpdateManager()
			{
				if (s_pInstance == this)
				{
					s_pInstance = nullptr;
				}
			}

			void UpdateManager::addFrameUpdateTimer(IFrameUpdateTimer* const &a_pUpdatableObject)
			{
				s_pInstance->m_listUpdateTimer.push_back(a_pUpdatableObject);
			}

			void UpdateManager::removeFrameUpdateTimer(IFrameUpdateTimer* const &a_pUpdatableObject)
			{
				FRAME_UPDATE_CONTAINER& l_refFrameUpdateList = s_pInstance->m_listUpdateTimer;

				auto l_FoundUpdateTimer = std::find(l_refFrameUpdateList.begin(), l_refFrameUpdateList.end(), a_pUpdatableObject);

				if (l_FoundUpdateTimer != l_refFrameUpdateList.end())
				{
					l_refFrameUpdateList.remove(*l_FoundUpdateTimer);
				}
			}

			void UpdateManager::addLateUpdateTimer(ILateUpdateTimer* const &a_pUpdatableObject)
			{
				s_pInstance->m_listLateUpdateTimer.push_back(a_pUpdatableObject);
			}

			void UpdateManager::removeLateUpdateTimer(ILateUpdateTimer* const &a_pLateUpdatableObject)
			{
				LATE_UPDATE_CONTAINER& l_refLateUpdateList = s_pInstance->m_listLateUpdateTimer;
				
				auto l_FoundLateUpdateTimer = std::find(l_refLateUpdateList.begin(), l_refLateUpdateList.end(), a_pLateUpdatableObject);

				if (l_FoundLateUpdateTimer != l_refLateUpdateList.end())
				{
					l_refLateUpdateList.remove(*l_FoundLateUpdateTimer);
				}
			}

			void UpdateManager::onUpdateFrame(const float a_fDeltaTimer)
			{
				for (auto l_CurrentIFrameUpdate = m_listUpdateTimer.cbegin(),
					l_EndIFrameUpdate = m_listUpdateTimer.cend();
					l_CurrentIFrameUpdate != l_EndIFrameUpdate; l_CurrentIFrameUpdate++)
				{
					IFrameUpdateTimer& l_refCurrentIFrameUpdate = **l_CurrentIFrameUpdate;
					if(l_refCurrentIFrameUpdate.m_bIsUpdatable)
					{
						l_refCurrentIFrameUpdate.onUpdate(a_fDeltaTimer);
					}
				}
			}

			void UpdateManager::onUpdateLateFrame(const float a_fDeltaTimer)
			{
				for (auto l_CurrentILateUpdate = m_listLateUpdateTimer.cbegin(),
					l_EndILateUpdate = m_listLateUpdateTimer.cend();
					l_CurrentILateUpdate != l_EndILateUpdate; l_CurrentILateUpdate++)
				{
					ILateUpdateTimer& l_refCurrentILateUpdate = **l_CurrentILateUpdate;
					if (l_refCurrentILateUpdate.m_bIsUpdatable)
					{
						l_refCurrentILateUpdate.onLateUpdate(a_fDeltaTimer);
					}
				}
			}

			int UpdateManager::getFrameUpdateObjectCount() const
			{
				return m_listUpdateTimer.size();
			}

			int UpdateManager::getLateUpdateObjectCount() const
			{
				return m_listLateUpdateTimer.size();
			}
	}
}