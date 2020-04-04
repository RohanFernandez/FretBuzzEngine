#pragma once
#include <iostream>
#include "delegate_base.h"

namespace ns_fretBuzz
{
	template<typename T> class Delegate;

	template<typename T_RET_TYPE, typename ...T_ARGS>
	class Delegate <T_RET_TYPE(T_ARGS...)> : protected DelegateBase<T_RET_TYPE(T_ARGS...)>
	{
	public:
		///Add member function contained within given class type into the delagte list
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)>
		void Add(T_CLASS_TYPE* a_TObject)
		{
			DelegateBase<T_RET_TYPE(T_ARGS...)>::template Add<T_CLASS_TYPE, T_METHOD>(a_TObject);
		}

		///Adds const member function contained within given class type into the delagte 
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...) const>
		void Add(T_CLASS_TYPE* const a_TObject)
		{
			DelegateBase<T_RET_TYPE(T_ARGS...)>::template Add<T_CLASS_TYPE, T_METHOD>(a_TObject);
		}

		///Adds static functionn into delegate list
		template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
		void Add()
		{
			DelegateBase<T_RET_TYPE(T_ARGS...)>::template Add<T_METHOD>();
		}

		///Calls the function stored in the delegate list
		T_RET_TYPE Invoke(T_ARGS... a_Args) throw(std::out_of_range)
		{
			try
			{
				return DelegateBase<T_RET_TYPE(T_ARGS...)>::Invoke(a_Args...);
			}
			catch (std::out_of_range& a_Exception)
			{
				std::cout << "DelegateError::Cannot invoke::" << a_Exception.what() << "\n";
			}
		}

		///removes a member function from the collection of actions
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)>
		void Remove(T_CLASS_TYPE* a_Instance)
		{
			DelegateBase<T_RET_TYPE(T_ARGS...)>::template Remove<T_CLASS_TYPE, T_METHOD>(a_Instance);
		}

		///removes a const member function from the collection of actions
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...) const>
		void Remove(T_CLASS_TYPE* const a_Instance)
		{
			DelegateBase<T_RET_TYPE(T_ARGS...)>::template Remove<T_CLASS_TYPE, T_METHOD>(a_Instance);
		}

		///removes an static or global action from the collection of actions
		template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
		void Remove()
		{
			DelegateBase<T_RET_TYPE(T_ARGS...)>::template Remove<T_METHOD>();
		}

		T_RET_TYPE operator()(T_ARGS... a_Args)
		{
			return Invoke(a_Args...);
		}

		///Clears the stored actions of type withing the delegate
		void Clear()
		{
			DelegateBase<T_RET_TYPE(T_ARGS...)>::Clear();
		}
	};
}
