#pragma once
#include "managed_resource.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class  ResourceManager
		{
		private:
			friend class AssetLoader;

			///singleton instance
			static ResourceManager* s_pInstance;

			static void destroyResource(IManagedResource* a_pManagedResource);

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
						s_pInstance->destroyResource(m_pResource);
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
						ENGINE_ERROR("ResourceManager::addResourceData:: Resource with name '{0}' cannot be added because a resource with the same name and type name '{1}' already exists.", a_strResourceName, typeid(a_Resource).name());
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

					//ENGINE_WARN("ResourceManager::getResource:: Resource with name '{0}' does not exist.", a_strResourceName);
					return nullptr;
				}
			};

			using T_MAP_RESOURCE = std::map<std::type_index, IResource*>;
			T_MAP_RESOURCE m_mapResource;

			///destroys resource and removes from the list
			template<typename T, typename = typename std::enable_if<std::is_base_of<IManagedResource, T>::value>::type>
			static void destroyResource(std::string a_strResourceName)
			{
				T_MAP_RESOURCE& l_mapResourceRef = s_pInstance->m_mapResource;
				const std::type_info& l_typeInfo = typeid(T);

				if (l_mapResourceRef.end() == l_mapResourceRef.find(l_typeInfo))
				{
					ENGINE_WARN("ResourceManager::destroyResource:: Could not find resource with typename '{0}' with name '{1}'", l_typeInfo.name(), a_strResourceName);
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
							destroyResource(*l_CurrResourceData);
							l_currentVectResourceData.erase(l_CurrResourceData);
							l_bIsResourceDataFound = true;
							break;
						}
					}

					if (!l_bIsResourceDataFound)
					{
						ENGINE_WARN("ResourceManager::destroyResource:: Could not find resource with name '{0}' with typename '{1}'", a_strResourceName, l_typeInfo.name());
					}
				}
			}

			ResourceManager();
			~ResourceManager();

		public:

			static ResourceManager* initialize();
			void destroy();
			static const ResourceManager* get();

			///Returns a const ptr to resource.
			template<typename T, typename = typename std::enable_if<std::is_base_of<IManagedResource, T>::value>::type>
			static T* getResource(std::string a_strResourceName)
			{
				T_MAP_RESOURCE& l_mapResourceRef = s_pInstance->m_mapResource;
				const std::type_info& l_typeInfo = typeid(T);

				Resource<T>* l_pResource = nullptr;

				if (l_mapResourceRef.end() == l_mapResourceRef.find(l_typeInfo))
				{
					ENGINE_WARN("ResourceManager::getResource:: Resource with name '{0}' of type '{1}' does not exist in storage.", a_strResourceName,l_typeInfo.name());
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
			bool addResource(std::string a_strResourceName, T& a_TResource)
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

			template<typename T, typename = typename std::enable_if<std::is_base_of<IManagedResource, T>::value>::type>
			static bool s_addResource(std::string a_strResourceName, T& a_TResource)
			{
				return s_pInstance->addResource(a_strResourceName, a_TResource);
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
					ENGINE_WARN("ResourceManager::getResourceCount:: Resource with type name '{0}' does not exist in storage.", l_typeInfo.name());
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