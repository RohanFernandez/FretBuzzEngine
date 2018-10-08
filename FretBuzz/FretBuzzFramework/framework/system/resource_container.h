#pragma once
#include <vector>

namespace ns_fretBuzz
{
	template<typename T>
	class ResourceContainer
	{
	protected:
		std::vector<T*> m_vectResourceContainer;

		ResourceContainer()
		{
		
		}

		virtual ~ResourceContainer()
		{

		}

		void registerResource(T& a_Resource)
		{
			m_vectResourceContainer.push_back(&a_Resource);
		}

		void unregisterResource(T& a_Resource)
		{
			int l_iContainerCount = m_vectResourceContainer.size();
			
			for (auto l_Iterator = m_vectResourceContainer.begin(),
				l_iIteratorEnd = m_vectResourceContainer.end();
				l_Iterator != l_iIteratorEnd;
				l_Iterator++)
			{
				if (*l_Iterator == &a_Resource)
				{
					m_vectResourceContainer.erase(l_Iterator);
					return;
				}
				std::cout << "ResourceContainer::unregisterCamera:: Failed to find resource to unregister in "<< typeid(m_vectResourceContainer).name()<<" list\n";
			}
		}
	};
}