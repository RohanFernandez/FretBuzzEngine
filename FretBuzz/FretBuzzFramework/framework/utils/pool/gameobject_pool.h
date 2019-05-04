#pragma once
#include "object_pool.h"
#include <system/game_object.h>

namespace ns_fretBuzz
{
	template<typename T, typename... TArgs/*, typename = typename std::enable_if<std::is_base_of<ns_system::GameObject, T>::value>::type*/>
	class FRETBUZZ_API GameObjectPool: protected ObjectPool<T, TArgs...>
	{
	public:
		GameObjectPool(int a_iStart, TArgs... a_Args)
			: ObjectPool<T, TArgs...>(a_iStart, false, a_Args...)
		{
			for (auto l_PooledObject = this->m_Pool.begin(); l_PooledObject != this->m_Pool.end(); l_PooledObject++)
			{
				(*l_PooledObject)->setActive(false);
			}
		}

		virtual ~GameObjectPool() {};

		T* getGameObject(TArgs... a_Args)
		{
			T* l_pGameObj = ObjectPool<T, TArgs...>::getObject(a_Args...);
			return l_pGameObj;
		};

		virtual void returnToPool(T* a_pReturnObject)
		{
			a_pReturnObject->setActive(false);
			ObjectPool<T, TArgs...>::returnToPool(a_pReturnObject);
		};
	};
}