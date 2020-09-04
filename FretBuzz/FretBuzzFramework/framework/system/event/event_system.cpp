#include <fretbuzz_pch.h>
//#include "event_system.h"
//
//namespace FRETBUZZ
//{
//	//singleton instance
//	EventSystem* EventSystem::s_pInstance = nullptr;
//
//	EventSystem::EventSystem()
//	{
//	}
//
//	EventSystem::~EventSystem()
//	{
//		m_ManagerMap.clear();
//	}
//
//	EventSystem* EventSystem::Initialize()
//	{
//		if (s_pInstance != nullptr)
//		{
//			return nullptr;
//		}
//		s_pInstance = new EventSystem();
//		return s_pInstance;
//	}
//
//	void EventSystem::destroy()
//	{
//		if (s_pInstance != nullptr)
//		{
//			delete s_pInstance;
//			s_pInstance = nullptr;
//		}
//	}
//
//	EventManager* EventSystem::getEventManagerWithName(std::string a_strManagerName)
//	{
//		EventManager* l_pReturn = nullptr;
//		T_EVENT_MANAGER_MAP::iterator l_EventManagerIterator = m_ManagerMap.find(a_strManagerName);
//		if (l_EventManagerIterator != m_ManagerMap.end())
//		{
//			l_pReturn = &l_EventManagerIterator->second;
//		}
//		return l_pReturn;
//	}
//
//	void EventSystem::AddManager(std::string a_strManagerName)
//	{
//		EventManager* l_EventManager = getEventManagerWithName(a_strManagerName);
//		if (l_EventManager == nullptr)
//		{
//			m_ManagerMap.insert(std::pair(a_strManagerName, EventManager(a_strManagerName)));
//		}
//	}
//
//	void EventSystem::RemoveManager(std::string a_strManagerName)
//	{
//		EventManager* l_EventManager = getEventManagerWithName(a_strManagerName);
//		if (l_EventManager != nullptr)
//		{
//			m_ManagerMap.erase(a_strManagerName);
//		}
//	}
//
//}