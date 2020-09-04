#pragma once
#include "object_pool.h"
#include <system/game_object.h>

namespace FRETBUZZ
{
	template<typename T, typename = typename std::enable_if<std::is_base_of<GameObject, T>::value>::type>
	class  GameObjectPool: protected ObjectPool<T>
	{
	public:
		GameObjectPool()
			: ObjectPool<T>(false)
		{
		}

		virtual ~GameObjectPool() {};

		template<typename... TArgs>
		T* getGameObject(TArgs... a_Args)
		{
			return ObjectPool<T>::getObject(a_Args...);
		};

		virtual void returnToPool(T* a_pReturnObject)
		{
			a_pReturnObject->setActive(false);
			ObjectPool<T>::returnToPool(a_pReturnObject);
		};
	};
}