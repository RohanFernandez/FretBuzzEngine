#pragma once

namespace ns_fretBuzz
{
	namespace ns_system
	{
		template<typename T>
		class FRETBUZZ_API ObjectPool
		{
		protected:
			std::vector<T*> m_Pool;

			void addToPool()
			{
				m_Pool.emplace_back(new T());
			}

		public:
			ObjectPool(int a_iInitSize = 0)
			{
				for (int l_iCurrentIndex = 0; l_iCurrentIndex < a_iInitSize; l_iCurrentIndex++)
				{
					addToPool();
				}
			}

			~ObjectPool() 
			{
				for (auto l_Iterator = m_Pool.begin(); l_Iterator != m_Pool.end(); l_Iterator++)
				{
					delete *l_Iterator;
					m_Pool.erase(l_Iterator);
				}
			}

			// Returns managed object from pool stack
			T* getObject()
			{
				if (m_Pool.size() == 0)
				{
					addToPool();
				}
				return m_Pool.pop_back();
			}

			// Returns object back into the pool
			void returnToPool(T* a_pReturnObject)
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
}