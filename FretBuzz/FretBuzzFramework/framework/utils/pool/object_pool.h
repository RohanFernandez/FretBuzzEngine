#pragma once

namespace ns_fretBuzz
{
	template<typename T, typename ...TArgs>
	class FRETBUZZ_API ObjectPool
	{
	protected:
		std::vector<T*> m_Pool;
		const bool m_bIsPoolMemoryManaged = true;

		virtual void addToPool(TArgs... a_Args)
		{
			T* l_newObj = new T(a_Args...);
			m_Pool.emplace_back(l_newObj);
		}

	public:
		ObjectPool(int a_iInitSize, bool a_bIsPoolMemoryManaged, TArgs... a_Args)
			: m_bIsPoolMemoryManaged{a_bIsPoolMemoryManaged}
		{
			for (int l_iCurrentIndex = 0; l_iCurrentIndex < a_iInitSize; l_iCurrentIndex++)
			{
				addToPool(a_Args...);
			}
		}

		virtual ~ObjectPool() 
		{
			for (auto l_Iterator = m_Pool.begin(); l_Iterator != m_Pool.end();)
			{
				if (m_bIsPoolMemoryManaged)
				{
					delete *l_Iterator;
				}
				l_Iterator = m_Pool.erase(l_Iterator);
			}
		}

		// Returns managed object from pool stack
		virtual T* getObject(TArgs... a_Args)
		{
			if (m_Pool.size() == 0)
			{
				addToPool(a_Args...);
			}

			T* l_pReturnFromPool = m_Pool[m_Pool.size() - 1];
			m_Pool.pop_back();
			return l_pReturnFromPool;
		}

		// Returns object back into the pool
		virtual void returnToPool(T* a_pReturnObject)
		{
			if (a_pReturnObject == nullptr)
			{
				return;
			}

			auto l_FoundIterator = std::find(m_Pool.begin(), m_Pool.end(), a_pReturnObject);
			if (l_FoundIterator != m_Pool.end())
			{
				return;
			}
			m_Pool.push_back(a_pReturnObject);
		}
	};
}