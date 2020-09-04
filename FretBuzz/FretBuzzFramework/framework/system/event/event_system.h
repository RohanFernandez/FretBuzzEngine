//#pragma once
//#include <utils/Event/event_manager.h>
//
//namespace FRETBUZZ
//{
//	class EventSystem
//	{
//	private:
//		static EventSystem* s_pInstance;
//
//		EventSystem();
//		~EventSystem();
//
//		using T_EVENT_MANAGER_MAP = std::unordered_map<std::string, EventManager>;
//		T_EVENT_MANAGER_MAP m_ManagerMap;
//
//		EventManager* getEventManagerWithName(std::string a_strManagerName);
//
//	public:
//		static EventSystem* Initialize();
//		void destroy();
//
//		void AddManager(std::string a_strManagerName);
//		void RemoveManager(std::string a_strManagerName);
//
//		template<typename T_DELEGATE>
//		static void SubscribeEvent(std::string a_strManagerName, std::string a_strEventName, Delegate<T_DELEGATE>& a_Delegate)
//		{
//			EventManager* l_EventManager = s_pInstance->getEventManagerWithName(a_strEventName);
//			if (l_EventManager != null)
//			{
//				l_EventManager->subscribe<T_DELEGATE>(a_Delegate);
//			}
//		}
//
//		template<typename T_DELEGATE>
//		static void UnsubscribeEvent(std::string a_strManagerName, std::string a_strEventName, Delegate<T_DELEGATE>& a_Delegate)
//		{
//			EventManager* l_EventManager = s_pInstance->getEventManagerWithName(a_strEventName);
//			if (l_EventManager != null)
//			{
//				l_EventManager->unsubscribe<T_DELEGATE>(a_Delegate);
//			}
//		}
//
//		template<typename T_DELEGATE, typename ...T_ARGS>
//		static void InvokeEvent(std::string a_strManagerName, std::string a_strEventName, T_ARGS ... a_Args)
//		{
//			EventManager* l_EventManager = s_pInstance->getEventManagerWithName(a_strEventName);
//			if (l_EventManager != null)
//			{
//				l_EventManager->invoke<T_DELEGATE>(a_Delegate);
//			}
//		}
//	};
//}