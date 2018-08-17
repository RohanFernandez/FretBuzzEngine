#pragma once
#include <map>
#include <typeindex>
#include <string>
#include <vector>
#include <iostream>
#include "managed_resource.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class ResourceManager
		{
		private:
			///singleton instance
			static ResourceManager* s_pInstance;

			class IResource
			{
			public:
				IResource(){}

				virtual ~IResource() = 0
				{

				}
			};
			
			template<typename T, typename = typename std::enable_if<std::is_base_of<IManagedResource, T>::value>::type>
			class Resource : public IResource
			{
			public:
				Resource()
					: IResource()
				{
				
				}

				virtual ~Resource()
				{
					for (auto l_CurrResourceData = m_vectResourceData.begin(),
						l_EndResourceData = m_vectResourceData.end();
						l_CurrResourceData != l_EndResourceData;
						l_CurrResourceData++)
					{
						delete (*l_CurrResourceData);
						*l_CurrResourceData = nullptr;
					}
					m_vectResourceData.clear();
				}

				struct ResourceData
				{
					std::string m_strResourceName;
					T* m_pResource = nullptr;

					ResourceData(std::string a_strResourceName, T a_Resource)
						: m_strResourceName{ a_strResourceName }
					{
						m_pResource = new T{ a_Resource };
					}

					~ResourceData()
					{
						m_pResource->destroyResource();
						delete m_pResource;
						m_pResource = nullptr;
					}
				};

				std::vector<ResourceData*> m_vectResourceData;

				bool addResourceData(std::string a_strResourceName, T a_Resource)
				{
					bool l_bIsResourceFound = false;
					for (auto l_CurrResourceData = m_vectResourceData.cbegin(),
						l_EndResourceData = m_vectResourceData.cend();
						l_CurrResourceData != l_EndResourceData;
						l_CurrResourceData++ )
					{
						if (a_strResourceName.compare((*l_CurrResourceData)->m_strResourceName) == 0)
						{
							l_bIsResourceFound = true;
							break;
						}
					}

					if (l_bIsResourceFound)
					{
						std::cout << "ResourceManager::addResourceData:: Resource with name '" << a_strResourceName << "' cannot be added because a resource with the same name and type name '"<< typeid(a_Resource).name() <<"' already exists.\n";
						return false;
					}

					m_vectResourceData.emplace_back(new ResourceData(a_strResourceName, a_Resource));
					return true;
				}

				///Returns a resource with given input name
				T* getResource(std::string a_strResourceName)
				{
					for (auto l_CurrResourceData = m_vectResourceData.begin(),
						l_EndResourceData = m_vectResourceData.end();
						l_CurrResourceData != l_EndResourceData;
						l_CurrResourceData++)
					{
						if (a_strResourceName.compare((*l_CurrResourceData)->m_strResourceName) == 0)
						{
							return (*l_CurrResourceData)->m_pResource;
						}
					}

					std::cout << "ResourceManager::getResource:: Resource with name '" << a_strResourceName << "' does not exist\n";
					return nullptr;
				}
			};

			using T_MAP_RESOURCE = std::map<std::type_index, IResource*>;
			T_MAP_RESOURCE m_mapResource;

		public:
			ResourceManager();
			~ResourceManager();

			///Returns a const ptr to resource.
			template<typename T, typename = typename std::enable_if<std::is_base_of<IManagedResource, T>::value>::type>
			static T* getResource(std::string a_strResourceName)
			{
				T_MAP_RESOURCE& l_mapResourceRef = s_pInstance->m_mapResource;
				const std::type_info& l_typeInfo = typeid(T);

				Resource<T>* l_pResource = nullptr;

				if (l_mapResourceRef.end() == l_mapResourceRef.find(l_typeInfo))
				{
					std::cout << "ResourceManager::getResource:: Resource with name '" << a_strResourceName << "' of type '"<< l_typeInfo.name()<<"' does not exist in storage.\n";
					return nullptr;
				}
				else
				{
					l_pResource = dynamic_cast<Resource<T>*>(l_mapResourceRef[l_typeInfo]);
					return l_pResource->getResource(a_strResourceName);
				}
			}

			///Adds resource of type T
			template<typename T, typename = typename std::enable_if<std::is_base_of<IManagedResource, T>::value>::type>
			static bool addResource(std::string a_strResourceName, T& a_TResource)
			{
				T_MAP_RESOURCE& l_mapResourceRef = s_pInstance->m_mapResource;
				const std::type_info& l_typeInfo = typeid(a_TResource);

				Resource<T>* l_pResource = nullptr;

				if (l_mapResourceRef.end() == l_mapResourceRef.find(l_typeInfo))
				{
					l_pResource = new Resource<T>();
					l_mapResourceRef.insert({ l_typeInfo , static_cast<IResource*>(l_pResource) });
				}
				else
				{
					l_pResource = dynamic_cast<Resource<T>*>(l_mapResourceRef[l_typeInfo]);
				}

				return l_pResource->addResourceData(a_strResourceName, a_TResource);
			}

			///destroys resource and removes from the list
			template<typename T, typename = typename std::enable_if<std::is_base_of<IManagedResource, T>::value>::type>
			static void destroyResource(std::string a_strResourceName)
			{
				T_MAP_RESOURCE& l_mapResourceRef = s_pInstance->m_mapResource;
				const std::type_info& l_typeInfo = typeid(T);

				if (l_mapResourceRef.end() == l_mapResourceRef.find(l_typeInfo))
				{
					std::cout << "ResourceManager::destroyResource:: Could not find resource with typename '"<< l_typeInfo.name() << "' with name '"<< a_strResourceName <<"' \n";
				}
				else
				{
					Resource<T>* l_pResource = dynamic_cast<Resource<T>*>(l_mapResourceRef[l_typeInfo]);
					auto& l_currentVectResourceData = l_pResource->m_vectResourceData;

					bool l_bIsResourceDataFound = false;
					for (auto l_CurrResourceData = l_currentVectResourceData.begin(),
						l_EndResourceData = l_currentVectResourceData.end();
						l_CurrResourceData != l_EndResourceData;
						l_CurrResourceData++)
					{
						if ((*l_CurrResourceData)->m_strResourceName.compare(a_strResourceName) == 0)
						{
							l_currentVectResourceData.erase(l_CurrResourceData);
							l_bIsResourceDataFound = true;
							break;
						}
					}

					if (!l_bIsResourceDataFound)
					{
						std::cout << "ResourceManager::destroyResource:: Could not find resource with name'" << a_strResourceName << "' with typename '" << l_typeInfo.name() << "' \n";
					}
				}
			}

			///Returns the number of resource of type T that is included in the vector.
			template<typename T, typename = typename std::enable_if<std::is_base_of<IManagedResource, T>::value>::type>
			static int getResourceCount()
			{
				T_MAP_RESOURCE& l_mapResourceRef = s_pInstance->m_mapResource;
				const std::type_info& l_typeInfo = typeid(T);

				Resource<T>* l_pResource = nullptr;;

				if (l_mapResourceRef.end() == l_mapResourceRef.find(l_typeInfo))
				{
					std::cout << "ResourceManager::getResourceCount:: Resource with type name '"<< l_typeInfo.name() <<"' does not exist in storage.\n";
					return 0;
				}
				else
				{
					l_pResource = dynamic_cast<Resource<T>*>(l_mapResourceRef[l_typeInfo]);
					return l_pResource->m_vectResourceData.size();
				}
			}
		};
	}
}