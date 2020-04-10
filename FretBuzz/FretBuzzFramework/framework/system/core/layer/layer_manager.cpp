#include <fretbuzz_pch.h>
#include "layer_manager.h"


namespace ns_fretBuzz
{
	namespace ns_system
	{
		const std::string LayerManager::LAYER_NAME_DEFAULT = "DEFAULT";

		LayerManager* LayerManager::s_pInstance = nullptr;

		LayerManager::LayerManager(std::vector<std::string> a_vectLayerNames)
		{
			m_layerMap.reserve(Layer::MAX_CAPACITY_LAYERS);
			addLayer(LAYER_NAME_DEFAULT, LAYER_DEFAULT_ID);

			//setting index from 1 to 15 because LAYER_DEFAULT_ID = 0
			int l_iLayerIndex = 1; 
			for (auto& l_strLayer : a_vectLayerNames)
			{
				if(addLayer(l_strLayer, l_iLayerIndex))
				{
					l_iLayerIndex++;
				}
			}
		}

		LayerManager::~LayerManager() 
		{
		}

		LayerManager* LayerManager::initialize(std::vector<std::string> a_vectLayerNames)
		{
			if (s_pInstance != nullptr)
			{	
				return nullptr;
			}
			s_pInstance = new LayerManager(a_vectLayerNames);
			return s_pInstance;
		}

		void LayerManager::destroy()
		{
			if (s_pInstance == nullptr)
			{
				return;
			}
			delete s_pInstance;
			s_pInstance = nullptr;
		}

		bool LayerManager::addLayer(std::string a_strLayerName, int a_iLayerIndex)
		{
			T_LAYER_MAP_TYPE::const_iterator l_Layer = m_layerMap.find(a_strLayerName);
			if (l_Layer != m_layerMap.end())
			{
				std::cout << "LayerManager::addLayer:: Cannot add the layer " << a_strLayerName << " because it already exists\n";
				return false;
			}

			int l_iLayerCount = m_layerMap.size();
			if (l_iLayerCount >= (Layer::MAX_CAPACITY_LAYERS))
			{
				std::cout << "LayerManager::addLayer:: Cannot add the layer " << a_strLayerName << " because the layer list is full\n";
				return false;
			}

			m_layerMap.insert(std::pair<std::string, Layer>(a_strLayerName, Layer(a_strLayerName, a_iLayerIndex)));
			return true;
		}

		const Layer* LayerManager::getLayerIdByName(std::string a_strLayerName)
		{
			T_LAYER_MAP_TYPE::iterator l_Layer = s_pInstance->m_layerMap.find(a_strLayerName);
			if (l_Layer != s_pInstance->m_layerMap.end())
			{
				return &l_Layer->second;
			}

			return nullptr;
		}

		void LayerManager::printLayers()
		{
			for (T_LAYER_MAP_TYPE::iterator l_LayerIterator = m_layerMap.begin();
				l_LayerIterator != m_layerMap.end();
				l_LayerIterator++)
			{
				std::cout << "LayerName:\t\t" << l_LayerIterator->first.c_str() << "\t\tBIT: "<< l_LayerIterator->second.getID()<<"\n";
			}
		}
	}
}