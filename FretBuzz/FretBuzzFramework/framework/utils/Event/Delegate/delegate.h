//Project created by RohanFernandez
//repository : https://github.com/RohanFernandez/DankeDelegate

#pragma once
#include "action.h"
#include <vector>

namespace ns_fretBuzz
{
	template<typename T> class Delegate;

	template<typename T_RET_TYPE, typename ...T_ARGS>
	class Delegate <T_RET_TYPE(T_ARGS...)>
	{
	private:
		bool m_bIsReturnable = false;

		using T_ACTION = Action<T_RET_TYPE(T_ARGS...)>;

		///Set to store all the Actions of the same type
		std::vector<T_ACTION> m_vectActions;

		//removes action given if found
		void remove(T_ACTION& a_Action)
		{
			for (typename std::vector<T_ACTION>::iterator l_iterator = m_vectActions.begin();
				l_iterator != m_vectActions.end();
				l_iterator++)
			{
				if (l_iterator->isActionEqual(a_Action))
				{
					m_vectActions.erase(l_iterator);
					break;
				}
			}
		}

	public:
		Delegate()
		{
			if (typeid(T_RET_TYPE) != typeid(void))
			{
				m_bIsReturnable = true;
			}
		}

		///Adds a member function into the delegate list
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)>
		void Add(T_CLASS_TYPE* a_Instance)
		{
			m_vectActions.emplace_back(T_ACTION::template GetAction<T_CLASS_TYPE, T_METHOD>(a_Instance));
		}

		///Adds a const member function into the delegate list
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...) const>
		void Add(T_CLASS_TYPE* const a_Instance)
		{
			m_vectActions.emplace_back(T_ACTION::template GetAction<T_CLASS_TYPE, T_METHOD>(a_Instance));
		}

		///Adds an static or global action into the list
		template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
		void Add()
		{
			m_vectActions.emplace_back(T_ACTION::template GetAction<T_METHOD>());
		}

		///Adds an static or global action into the list
		void Add(Delegate<T_RET_TYPE(T_ARGS...)>& a_Delegate)
		{
			for (typename std::vector<T_ACTION>::iterator l_iterator = a_Delegate.m_vectActions.begin();
				l_iterator != a_Delegate.m_vectActions.end();
				l_iterator++)
			{
				m_vectActions.emplace_back(T_ACTION::GetAction(*l_iterator));
			}
		}

		///+= operator overloading to add actions of a delegate
		void operator+=(Delegate<T_RET_TYPE(T_ARGS...)>& a_Delegate)
		{
			Add(a_Delegate);
		}

		///operator overload to remove actions in a delegate
		void operator-=(Delegate<T_RET_TYPE(T_ARGS...)>& a_Delegate)
		{
			Remove(a_Delegate);
		}

		T_RET_TYPE operator()(T_ARGS... a_Args)
		{
			if (m_bIsReturnable)
			{
				return Invoke(a_Args...);
			}
			else
			{
				Invoke(a_Args...);
			}
		}

		///Calls all the actions stored within the delegate
		T_RET_TYPE Invoke(T_ARGS... a_Args)
		{
			try
			{
				if (m_vectActions.size() == 0)
				{
					throw std::out_of_range("Delegate is empty\n");
				}

				typename std::vector<T_ACTION>::iterator l_LastIterator = m_vectActions.end() - 1;
				for (typename std::vector<T_ACTION>::iterator l_iterator = m_vectActions.begin();
					l_iterator != m_vectActions.end();
					l_iterator++)
				{
					if (m_bIsReturnable && (l_LastIterator == l_iterator))
					{
						return l_iterator->Invoke(a_Args...);
					}
					else
					{
						l_iterator->Invoke(a_Args...);
					}
				}
			}
			catch (std::out_of_range& a_Exception)
			{
				std::cout << "Delegate Exception::Cannot invoke::" << a_Exception.what() << "\n";
			}
		}

		///removes a member function into the delegate list
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)>
		void Remove(T_CLASS_TYPE* a_Instance)
		{
			T_ACTION l_Action = T_ACTION::template GetAction<T_CLASS_TYPE, T_METHOD>(a_Instance);
			remove(l_Action);
		}

		///removes a const member function into the delegate list
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...) const>
		void Remove(T_CLASS_TYPE* const a_Instance)
		{
			T_ACTION l_Action = T_ACTION::template GetAction<T_CLASS_TYPE, T_METHOD>(a_Instance);
			remove(l_Action);
		}

		///removes an static or global action into the list
		template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
		void Remove()
		{
			T_ACTION l_Action = T_ACTION::template GetAction<T_METHOD>();
			remove(l_Action);
		}

		///removes all actions in the delegate if it exists
		void Remove(Delegate<T_RET_TYPE(T_ARGS...)>& a_Delegate)
		{
			for (typename std::vector<T_ACTION>::iterator l_iterator = a_Delegate.m_vectActions.begin();
				l_iterator != a_Delegate.m_vectActions.end();
				l_iterator++)
			{
				remove(*l_iterator);
			}
		}

		///Clears the stored actions of type withing the delegate
		void Clear()
		{
			m_vectActions.clear();
		}
	};

}