#pragma once
#include <string>
#include <unordered_map>
#include <utils/Event/Delegate/delegate.h>
#include <memory>

namespace ns_fretBuzz
{
	class EventManager
	{
	private:
		EventManager(std::string a_strName);
		~EventManager();

		std::string m_strName;

		using T_EVENT_MAP = std::unordered_map<std::string, std::shared_ptr<IDelegate>>;

		T_EVENT_MAP m_EventMap;

		//returns event with ID if exist else returns nullptr
		std::shared_ptr<IDelegate> getEventWithID(std::string a_strEventID);

		///Returns delegate ptr
		template<typename T_DELEGATE>
		Delegate<T_DELEGATE>* getDelegatePtr(std::string a_strEventID)
		{
			//Does event with ID already exist in the event map
			std::shared_ptr<IDelegate> l_FoundEvent = getEventWithID(a_strEventID);
			bool l_bIsEventWithIdExist = (l_FoundEvent != nullptr);

			if (!l_bIsEventWithIdExist)
			{
				l_FoundEvent = std::make_shared<Delegate<T_DELEGATE>>();
				m_EventMap.insert(std::pair < a_strEventID, l_FoundEvent);
			}

			return dynamic_cast<Delegate<T_DELEGATE>*>(l_FoundEvent.get());
		}

	public:

		template<typename T_DELEGATE>
		void subscribe(std::string a_strEventID, Delegate<T_DELEGATE> a_Delegate)
		{
			Delegate<T_DELEGATE>* l_pDelegate = getDelegatePtr(a_strEventID)
				if (l_pDelegate == nullptr)
				{
					return;
				}
			*l_pDelegate += a_Delegate;
		}

		template<typename T_DELEGATE>
		void unsubscribe(std::string a_strEventID, Delegate<T_DELEGATE> a_Delegate)
		{
			Delegate<T_DELEGATE>* l_pDelegate = getDelegatePtr(a_strEventID)
				if (l_pDelegate == nullptr)
				{
					return;
				}
			*l_pDelegate -= a_Delegate;
		}

		template<typename T_DELEGATE, typename ... T_ARGS>
		void invoke(std::string a_strEventID, T_ARGS... a_Args)
		{
			Delegate<T_DELEGATE>* l_pDelegate = getDelegatePtr(a_strEventID)
				if (l_pDelegate == nullptr)
				{
					return;
				}
			(*l_pDelegate)(a_Args...);
		}
	};
}