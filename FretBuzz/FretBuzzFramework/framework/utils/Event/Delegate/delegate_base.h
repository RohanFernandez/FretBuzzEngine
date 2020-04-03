#pragma once
#include <iostream>
#include "action.h"
#include <functional>
#include <typeinfo>
#include <set>

namespace ns_fretBuzz
{
	template<typename T> class DelegateBase;

	template<typename T_RET_TYPE, typename ...T_ARGS>
	class DelegateBase <T_RET_TYPE(T_ARGS...)>
	{
		private:

			using T_IACTION = IAction<T_RET_TYPE(T_ARGS...)>;

			///Set to store all the Actions of the same type
			std::set<T_IACTION*> m_SetActions;

			///Deletes all actions stored in the delegate list
			void DeleteAllActions()
			{
				for (typename std::set<T_IACTION*>::iterator l_iterator = m_SetActions.begin();
					l_iterator != m_SetActions.end();
					l_iterator++)
				{
					delete *l_iterator;
				}
			}

		protected:
			///Constructor, Instantiates the List that stores the Actions of type T_RET_TYPE(T_ARGS...)
			DelegateBase()
			{
			}

			///Destructor
			virtual ~DelegateBase()
			{
				DeleteAllActions();
			}

			///Adds a member function into the delegate list
			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)>
			void Add(T_CLASS_TYPE* a_Instance)
			{
				T_IACTION* l_pNewIAction = T_IACTION::template GetIAction<T_CLASS_TYPE, T_METHOD>(a_Instance);
				m_SetActions.insert(l_pNewIAction);
			}

			///Adds a const member function into the delegate list
			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...) const>
			void Add(T_CLASS_TYPE* const a_Instance)
			{
				T_IACTION* const l_pNewIFuzzyAction = T_IACTION::template GetIAction<T_CLASS_TYPE, T_METHOD>(a_Instance);
				m_SetActions.insert(const_cast<T_IACTION*>(l_pNewIFuzzyAction));
			}

			///Adds an static or global action into the list
			template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
			void Add()
			{
				T_IACTION* l_l_pNewIAction = T_IACTION::template GetIAction<T_METHOD>();
				m_SetActions.insert(l_l_pNewIAction);
			}

			///Calls all the actions stored within the delegate
			T_RET_TYPE Invoke(T_ARGS... a_Args) throw(std::out_of_range)
			{
				try
				{
					if (m_SetActions.size() == 0)
					{
						throw std::out_of_range("Delegate is empty\n");
					}

					T_RET_TYPE l_tReturn;
					for (typename std::set<T_IACTION*>::iterator l_iterator = m_SetActions.begin();
						l_iterator != m_SetActions.end();
						l_iterator++)
					{
						l_tReturn = (*l_iterator)->Invoke(a_Args...);
					}

					if (typeid(T_RET_TYPE) != typeid(void))
					{
						return l_tReturn;
					}
				}
				catch (std::out_of_range& a_Exception)
				{
					throw;
				}
			}

			///removes a member function into the delegate list
			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)>
			void Remove(T_CLASS_TYPE* a_Instance)
			{
				for (typename std::set<T_IACTION*>::iterator l_iterator = m_SetActions.begin();
					l_iterator != m_SetActions.end();
					l_iterator++)
				{
					if ((*l_iterator)->isActionEqual<T_CLASS_TYPE, T_METHOD>(a_Instance))
					{
						delete (*l_iterator);
						m_SetActions.erase(l_iterator);
						break;
					}
				}
			}

			///removes a const member function into the delegate list
			template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...) const>
			void Remove(T_CLASS_TYPE* const a_Instance)
			{
				for (typename std::set<T_IACTION*>::iterator l_iterator = m_SetActions.begin();
					l_iterator != m_SetActions.end();
					l_iterator++)
				{
					if ((*l_iterator)->isActionEqual<T_CLASS_TYPE, T_METHOD>(a_Instance))
					{
						delete (*l_iterator);
						m_SetActions.erase(l_iterator);
						break;
					}
				}
			}

			///removes an static or global action into the list
			template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
			void Remove()
			{
				for (typename std::set<T_IACTION*>::iterator l_iterator = m_SetActions.begin();
					l_iterator != m_SetActions.end();
					l_iterator++)
				{
					if ((*l_iterator)->isActionEqual<T_METHOD>())
					{
						delete (*l_iterator);
						m_SetActions.erase(l_iterator);
						break;
					}
				}
			}

			///Clears the stored actions of type withing the delegate
			void Clear()
			{
				DeleteAllActions();
				m_SetActions.clear();
			}
	};

}