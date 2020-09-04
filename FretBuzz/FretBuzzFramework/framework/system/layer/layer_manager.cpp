#include <fretbuzz_pch.h>
#include "layer_manager.h"
#include <iomanip>

namespace FRETBUZZ
{
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
		printLayers();
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

	bool LayerManager::addLayer(const std::string& a_strLayerName, int a_iLayerIndex)
	{
		T_LAYER_MAP_TYPE::const_iterator l_Layer = m_layerMap.find(a_strLayerName);
		if (l_Layer != m_layerMap.end())
		{
			std::cout << "LayerManager::addLayer:: Cannot add the layer " << a_strLayerName << " because it already exists\n";
			return false;
		}

		size_t l_iLayerCount = m_layerMap.size();
		if (l_iLayerCount >= (Layer::MAX_CAPACITY_LAYERS))
		{
			std::cout << "LayerManager::addLayer:: Cannot add the layer " << a_strLayerName << " because the layer list is full\n";
			return false;
		}

		m_layerMap.insert(std::pair<std::string, Layer>(a_strLayerName, Layer(a_strLayerName, a_iLayerIndex)));
		return true;
	}

	Layer* LayerManager::getLayerByName(const std::string& a_strLayerName)
	{
		T_LAYER_MAP_TYPE::iterator l_Layer = m_layerMap.find(a_strLayerName);
		if (l_Layer != m_layerMap.end())
		{
			return &l_Layer->second;
		}

		return nullptr;
	}

	const Layer* LayerManager::GetLayerByName(const std::string& a_strLayerName)
	{
		return s_pInstance->getLayerByName(a_strLayerName);
	}

	const Layer* LayerManager::GetLayerByID(int a_iID)
	{
		for (auto& l_strLayer : s_pInstance->m_layerMap)
		{
			if (l_strLayer.second.getID() == a_iID)
			{
				return &l_strLayer.second;
			}
		}
		return nullptr;
	}

	void LayerManager::printLayers()
	{
		std::stringstream l_strStream;
		l_strStream << "\n";
		for (T_LAYER_MAP_TYPE::iterator l_LayerIterator = m_layerMap.begin();
			l_LayerIterator != m_layerMap.end();
			l_LayerIterator++)
		{
			l_strStream << "LayerName:\t\t" 
						<< std::setw(10) 
						<< l_LayerIterator->first.c_str() 
						<< "\t\tBIT: " << l_LayerIterator->second.getID() 
						<< "\n";
		}
		ENGINE_INFO(l_strStream.str());
	}
}