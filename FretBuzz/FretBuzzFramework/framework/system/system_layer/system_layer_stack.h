#pragma once
#include "system_layer_base.h"
#include <utils/resource_container.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class SystemLayerStack : ResourceContainer<SystemLayerBase*>
		{
		private:
			//singleton
			static SystemLayerStack* s_pInstance;

			SystemLayerStack(int a_iStackSize = 2);
			~SystemLayerStack();

			std::vector<SystemLayerBase*> m_vectLayers;

		public:
			static SystemLayerStack* Initialize(int a_iStackSize);
			void destroy();

			std::vector<SystemLayerBase*>::iterator begin() { return m_vectLayers.begin(); }
			std::vector<SystemLayerBase*>::iterator end() { return m_vectLayers.end(); }

			template<class T_SYSTEM_LAYER, typename = typename std::enable_if<std::is_base_of<SystemLayerBase, T_SYSTEM_LAYER>::value>::type>
			static void AddLayer(const std::string& a_strLayerName)
			{
				T_SYSTEM_LAYER* l_pSystemLayer = new T_SYSTEM_LAYER();
				s_pInstance->m_vectLayers.emplace_back(l_pSystemLayer);
				l_pSystemLayer->onAttach();
			}

			static void RemoveLayer(const std::string& a_strLayerName);
		};
	}
}