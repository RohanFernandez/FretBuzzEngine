//Project created by RohanFernandez
//repository : https://github.com/RohanFernandez/DankeDelegate

#pragma once

namespace FRETBUZZ
{
	template<typename T1> class Action;

	template<typename T_RET_TYPE, typename ...T_ARGS>
	class Action <T_RET_TYPE(T_ARGS...)>
	{
	private:
		///Function template
		using FUNC_STUB = T_RET_TYPE(*)(void*, T_ARGS...);

		///Function pointer of the delegate type to be called
		FUNC_STUB m_pFuncStub = nullptr;

		///Pointer to the object which cointains the function to be called
		void* m_pObjectPtr = nullptr;

#pragma region FUNCTION BLUEPRINT

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

#pragma endregion FUNCTION BLUEPRINT

	public:
		Action() = delete;

#pragma region CONSTRUCTOR

		///Return an Action of member type 
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)>
		static Action <T_RET_TYPE(T_ARGS...)> GetAction(T_CLASS_TYPE*& a_pInstance)
		{
			return Action(a_pInstance, FunctionBlueprint<T_CLASS_TYPE, T_METHOD>);
		}

		///Return an Action of const member type 
		template<typename T_CLASS_TYPE, T_RET_TYPE(T_CLASS_TYPE::* T_METHOD)(T_ARGS...)const>
		static Action <T_RET_TYPE(T_ARGS...)> GetAction(T_CLASS_TYPE* const a_pInstance)
		{
			return Action(a_pInstance, FunctionBlueprint<T_CLASS_TYPE, T_METHOD>);
		}

		///Return an Action of static / global type 
		template<T_RET_TYPE(*T_METHOD)(T_ARGS...)>
		static Action <T_RET_TYPE(T_ARGS...)> GetAction()
		{
			return Action(nullptr, FunctionBlueprint<T_METHOD>);
		}

		///Return an Action of static / global type 
		static Action <T_RET_TYPE(T_ARGS...)> GetAction(Action <T_RET_TYPE(T_ARGS...)>& a_Action)
		{
			return Action <T_RET_TYPE(T_ARGS...)>(a_Action.m_pObjectPtr, a_Action.m_pFuncStub);
		}

#pragma endregion CONSTRUCTOR

#pragma region IS_ACTION_EQUAL_TO

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

		//checks if the action provided is equal to this action
		bool isActionEqual(Action& a_Action)
		{
			return (a_Action.m_pFuncStub == m_pFuncStub) &&
				(a_Action.m_pObjectPtr == m_pObjectPtr);
		}

#pragma endregion IS_ACTION_EQUAL_TO

		///Calls the function
		T_RET_TYPE Invoke(T_ARGS... a_Args) const
		{
			return (*m_pFuncStub)(m_pObjectPtr, a_Args...);
		}

		void operator=(Action&& a_Action)
		{
			m_pFuncStub = a_Action.m_pFuncStub;
			m_pObjectPtr = a_Action.m_pObjectPtr;
		}

		///Constructor
		Action(void* a_pObj, FUNC_STUB a_pFuncStub)
		{
			m_pObjectPtr = a_pObj;
			m_pFuncStub = a_pFuncStub;
		}

		///Constructor
		Action(Action& a_Action)
			: Action(a_Action.m_pObjectPtr, a_Action.m_pFuncStub)
		{
		}

		///Constructor
		Action(Action&& a_Action)
			: Action(a_Action.m_pObjectPtr, a_Action.m_pFuncStub)
		{
		}
	};
}