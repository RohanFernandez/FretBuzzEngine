#pragma once
#include <iostream>
#include <functional>

namespace ns_fretBuzz
{
	template<typename T1> class Action;

#pragma region Interface for an Action

	///Interface to a single action, an action can only be called via this interface
	template<typename T1> class IAction;

	template <typename T_RET_TYPE, typename ...T_ARGS>
	class IAction<T_RET_TYPE(T_ARGS...)>
	{
	public:

		///Calls the function with arguements
		virtual T_RET_TYPE Invoke(T_ARGS... a_Args) const = 0;

		virtual ~IAction()
		{
		}

		///Return an Action of member type 
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)>
		static IAction<T_RET_TYPE(T_ARGS...)>* GetIAction(T_CLASS_TYPE*& a_pInstance)
		{
			return static_cast<IAction<T_RET_TYPE(T_ARGS...)>*>(Action<T_RET_TYPE(T_ARGS...)>::template GetAction<T_CLASS_TYPE, T_METHOD>(a_pInstance));
		}

		///Return an Action of const member type 
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)const>
		static IAction<T_RET_TYPE(T_ARGS...)>* GetIAction(T_CLASS_TYPE* const a_pInstance)
		{
			return static_cast<IAction<T_RET_TYPE(T_ARGS...)>*>(Action<T_RET_TYPE(T_ARGS...)>::template GetAction<T_CLASS_TYPE, T_METHOD>(a_pInstance));
		}

		///Return an Action of static / global type 
		template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
		static IAction<T_RET_TYPE(T_ARGS...)>* GetIAction()
		{
			return static_cast<IAction<T_RET_TYPE(T_ARGS...)>*>(Action<T_RET_TYPE(T_ARGS...)>::template GetAction<T_METHOD>());
		}

		//checks if the action provided is equal to the object& function pointer
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)>
		bool isActionEqual(T_CLASS_TYPE* a_pActionObjectToFind)
		{
			Action<T_RET_TYPE(T_ARGS...)>* l_pAction = dynamic_cast<Action<T_RET_TYPE(T_ARGS...)>*>(this);
			if (l_pAction != nullptr)
			{
				return l_pAction->isActionEqual<T_CLASS_TYPE, T_METHOD>(a_pActionObjectToFind);
			}
			
			return false;
		}

		//checks if the const function in the action provided is equal to the object& function pointer
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...) const>
		bool isActionEqual(T_CLASS_TYPE* const a_pActionObjectToFind)
		{
			Action<T_RET_TYPE(T_ARGS...)>* l_pAction = dynamic_cast<Action<T_RET_TYPE(T_ARGS...)>*>(this);
			if (l_pAction != nullptr)
			{
				return l_pAction->isActionEqual<T_CLASS_TYPE, T_METHOD>(a_pActionObjectToFind);
			}

			return false;
		}

		//checks if the action provided is equal to the object& function pointer
		template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
		bool isActionEqual()
		{
			Action<T_RET_TYPE(T_ARGS...)>* l_pAction = dynamic_cast<Action<T_RET_TYPE(T_ARGS...)>*>(this);
			if (l_pAction != nullptr)
			{
				return l_pAction->isActionEqual<T_METHOD>();
			}

			return false;
		}
	};
#pragma endregion Interface for an Action


#pragma region Action

	template<typename T_RET_TYPE, typename ...T_ARGS>
	class Action <T_RET_TYPE(T_ARGS...)> : public IAction<T_RET_TYPE(T_ARGS...)>
	{
		///PRIVATE VARIABLES
	private:
		///Function template
		using FUNC_STUB = T_RET_TYPE(*)(void*, T_ARGS...);

		///Function pointer of the delegate type to be called
		FUNC_STUB m_pFuncStub = nullptr;

		///Pointer to the object which cointains the function to be called
		void* m_pObjectPtr = nullptr;

		///PRIVATE SOURCE
	private:

		///Constructor
		Action(void* a_pObj, FUNC_STUB a_pFuncStub)
		{
			m_pObjectPtr = a_pObj;
			m_pFuncStub = a_pFuncStub;
		}

		///Return an Action of member type 
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)>
		static Action<T_RET_TYPE(T_ARGS...)>* GetAction(T_CLASS_TYPE*& a_pInstance)
		{
			return new Action<T_RET_TYPE(T_ARGS...)>(a_pInstance, FunctionBlueprint<T_CLASS_TYPE, T_METHOD>);
		}

		///Return an Action of const member type 
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)const>
		static Action<T_RET_TYPE(T_ARGS...)>* GetAction(T_CLASS_TYPE* const a_pInstance)
		{
			return new Action<T_RET_TYPE(T_ARGS...)>(a_pInstance, FunctionBlueprint<T_CLASS_TYPE, T_METHOD>);
		}

		///Return an Action of static / global type 
		template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
		static Action<T_RET_TYPE(T_ARGS...)>* GetAction()
		{
			return new Action<T_RET_TYPE(T_ARGS...)>(nullptr, FunctionBlueprint<T_METHOD>);
		}

	public:

		friend class IAction<T_RET_TYPE(T_ARGS...)>;

		///Constructor
		Action() = delete;

	protected:

		///Acts as a member function template
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)>
		static T_RET_TYPE FunctionBlueprint(void* a_pObj, T_ARGS... a_Args)
		{
			T_CLASS_TYPE* l_Obj = static_cast<T_CLASS_TYPE*>(a_pObj);
			return (l_Obj->*T_METHOD)(a_Args...);
		}

		///Acts as a const member function template
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...) const>
		static T_RET_TYPE FunctionBlueprint(void* a_pObj, T_ARGS... a_Args)
		{
			T_CLASS_TYPE* l_Obj = static_cast<T_CLASS_TYPE*>(a_pObj);
			return (l_Obj->*T_METHOD)(a_Args...);
		}

		///Acts as a static function template
		template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
		static T_RET_TYPE FunctionBlueprint(void* a_pObj, T_ARGS... a_Args)
		{
			return (*T_METHOD)(a_Args...);
		}

		///Calls the function
		virtual T_RET_TYPE Invoke(T_ARGS... a_Args) const override
		{
			return (*m_pFuncStub)(m_pObjectPtr, a_Args...);
		}

		//checks if the action provided is equal to the object& function pointer
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::*T_METHOD)(T_ARGS...)>
		bool isActionEqual(T_CLASS_TYPE* a_pActionObjectToFind)
		{
			return (FunctionBlueprint<T_CLASS_TYPE, T_METHOD> == m_pFuncStub) &&
				a_pActionObjectToFind == m_pObjectPtr;
		}

		//checks if the action provided is equal to the object& function pointer
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...) const>
		bool isActionEqual(T_CLASS_TYPE* const a_pActionObjectToFind)
		{
			return (FunctionBlueprint<T_CLASS_TYPE, T_METHOD> == m_pFuncStub) &&
				a_pActionObjectToFind == m_pObjectPtr;
		}

		//checks if the static function of the action provided is equal to the object& function pointer
		template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
		bool isActionEqual()
		{
			return (FunctionBlueprint<T_METHOD> == m_pFuncStub)&&
				nullptr == m_pObjectPtr;
		}
	};

#pragma endregion Action

}