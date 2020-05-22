#include <fretbuzz_pch.h>
#include <event_manager.h>

namespace ns_fretBuzz
{
	EventManager::EventManager(std::string a_strName)
		: m_strName{ a_strName }
	{

	}

	EventManager::~EventManager()
	{
	
	}

	std::shared_ptr<IDelegate> EventManager::getEventWithID(std::string a_strEventID)
	{
		T_EVENT_MAP::iterator l_FoundEventIterator = m_EventMap.find(a_strEventID);
		std::shared_ptr<IDelegate> l_Return = nullptr;
		if (l_FoundEventIterator == m_EventMap.end())
		{
			l_Return = l_FoundEventIterator->second;
		}
		return l_Return;
	}
}