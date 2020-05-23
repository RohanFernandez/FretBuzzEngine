#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <utils/Event/delegate.h>

namespace ns_fretBuzz
{
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		static EventManager* Initialize();
		void destroy();

	private:
		//singleton instance
		static EventManager* s_pInstance;

		using T_EVENT_MAP = std::unordered_map<std::string, IDelegate*>;

		T_EVENT_MAP m_EventMap;

		//returns event with ID if exist else returns nullptr
		IDelegate* getEventWithID(std::string a_strEventID);

		///Returns delegate ptr
		template<typename T_DELEGATE>
		Delegate<T_DELEGATE>* getDelegatePtr(std::string a_strEventID)
		{
			//Does event with ID already exist in the event map
			IDelegate* l_pFoundEvent = getEventWithID(a_strEventID);
			bool l_bIsEventWithIdExist = (l_pFoundEvent != nullptr);

			if (!l_bIsEventWithIdExist)
			{
				l_pFoundEvent = static_cast<IDelegate*>(new Delegate<T_DELEGATE>());
				std::pair<std::string, IDelegate*> l_EventPair(a_strEventID, l_pFoundEvent);
				m_EventMap.insert(l_EventPair);
			}

			return dynamic_cast<Delegate<T_DELEGATE>*>(l_pFoundEvent);
		}

	public:

		template<typename T_DELEGATE>
		static void Subscribe(std::string a_strEventID, Delegate<T_DELEGATE>& a_Delegate)
		{
			Delegate<T_DELEGATE>* l_pDelegate = s_pInstance->getDelegatePtr<T_DELEGATE>(a_strEventID);
				if (l_pDelegate == nullptr)
				{
					return;
				}
			*l_pDelegate += a_Delegate;
		}

		template<typename T_DELEGATE>
		static void Unsubscribe(std::string a_strEventID, Delegate<T_DELEGATE>& a_Delegate)
		{
			Delegate<T_DELEGATE>* l_pDelegate = s_pInstance->getDelegatePtr<T_DELEGATE>(a_strEventID);
				if (l_pDelegate == nullptr)
				{
					return;
				}
			*l_pDelegate -= a_Delegate;
		}

		template<typename T_DELEGATE, typename ... T_ARGS>
		static void Invoke(std::string a_strEventID, T_ARGS... a_Args)
		{
			Delegate<T_DELEGATE>* l_pDelegate = s_pInstance->getDelegatePtr<T_DELEGATE>(a_strEventID);
				if (l_pDelegate == nullptr)
				{
					return;
				}
			(*l_pDelegate)(a_Args...);
		}
	};
}