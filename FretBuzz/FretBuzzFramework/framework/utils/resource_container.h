#pragma once

namespace ns_fretBuzz
{
	template<typename T_CONTAINER_TYPE>
	class FRETBUZZ_API ResourceContainer{};

	template<typename T>
	class FRETBUZZ_API ResourceContainer<std::vector<T>>
	{
	protected:
		std::vector<T> m_Container;

		ResourceContainer(){}
		virtual ~ResourceContainer(){}

		void registerResource(T& a_Resource)
		{
			m_Container.push_back(a_Resource);
		}

		void unregisterResource(T& a_Resource)
		{
			int l_iContainerCount = m_Container.size();

			for (auto l_Iterator = m_Container.begin(),
				l_iIteratorEnd = m_Container.end();
				l_Iterator != l_iIteratorEnd;
				l_Iterator++)
			{
				if (*l_Iterator == a_Resource)
				{
					m_Container.erase(l_Iterator);
					return;
				}
				std::cout << "ResourceContainer::unregisterCamera:: Failed to find resource to unregister in " << typeid(m_Container).name() << " list\n";
			}
		}
	};

	template<typename T_KEY, typename T_VALUE>
	class ResourceContainer<std::map<T_KEY, T_VALUE>>
	{
	protected:
		using T_CONTAINER_TYPE = std::map<T_KEY, T_VALUE>;
		std::map<T_KEY, T_VALUE> m_Container;

		ResourceContainer() {};
		virtual ~ResourceContainer() {};

		void registerResource(T_KEY a_Key, T_VALUE a_Value)
		{
			auto l_Iterator = m_Container.find(a_Key);
			if (l_Iterator == m_Container.end())
			{
				m_Container.insert(std::pair<T_KEY, T_VALUE>(a_Key, a_Value));
			}
			else
			{
				std::cout << "ResourceContainer:: registerResource:: Failed to register key because the key already exists.\n";
			}
		}

		T_VALUE unregisterResource(T_KEY a_Key)
		{
			auto l_Iterator = m_Container.find(a_Key);
			T_VALUE l_Return = nullptr;

			if (l_Iterator != m_Container.end())
			{
				l_Return = l_Iterator->second;
				m_Container.erase(l_Iterator);
			}
			else
			{
				std::cout << "ResourceContainer:: unregisterResource:: Failed to unregister key because the key does not exist.\n";
			}

			return l_Return;
		}

		T_VALUE getResource(T_KEY a_Key)
		{
			auto l_Iterator = m_Container.find(a_Key);
			if (l_Iterator != m_Container.end())
			{
				return l_Iterator->second;
			}
			else
			{
				std::cout << "ResourceContainer:: get:: Failed to retrieve value with key.\n";
				return nullptr;
			}
		}
	};
}