#include <fretbuzz_pch.h>
#include "event_manager.h"

namespace FRETBUZZ
{
	///singleton instance
	EventManager* EventManager::s_pInstance = nullptr;

	EventManager::EventManager()
	{

	}

	EventManager::~EventManager()
	{
		for (T_EVENT_MAP::iterator l_EventIterator = m_EventMap.begin();
			l_EventIterator != m_EventMap.end(); l_EventIterator++)
		{
			IDelegate*& l_pDelegate = l_EventIterator->second;
			if (l_pDelegate != nullptr)
			{
				delete l_pDelegate;
				l_pDelegate = nullptr;
			}
		}
	}

	EventManager* EventManager::Initialize()
	{
		if (s_pInstance != nullptr)
		{
			return nullptr;
		}
		s_pInstance = new EventManager();
		return s_pInstance;
	}

	void EventManager::destroy()
	{
		if (s_pInstance != nullptr)
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}

	IDelegate* EventManager::getEventWithID(std::string a_strEventID)
	{
		T_EVENT_MAP::iterator l_FoundEventIterator = m_EventMap.find(a_strEventID);
		IDelegate* l_pReturn = nullptr;
		if (l_FoundEventIterator != m_EventMap.end())
		{
			l_pReturn = l_FoundEventIterator->second;
		}
		return l_pReturn;
	}
}