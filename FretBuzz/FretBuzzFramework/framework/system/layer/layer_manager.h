#pragma once
#include <bitset>
#include "layer.h"

namespace FRETBUZZ
{
	class  LayerManager
	{
	public:
		using T_LAYER_MAP_TYPE = std::unordered_map<std::string, Layer>;

	private:

		//singleton instance
		static LayerManager* s_pInstance;

		T_LAYER_MAP_TYPE m_layerMap;

		LayerManager(std::vector<std::string> a_vectLayerNames);
		~LayerManager();

		bool addLayer(const std::string& a_strLayerName, int a_iLayerIndex);
		Layer* getLayerByName(const std::string& a_strLayerName);

	public:
		static LayerManager* initialize(std::vector<std::string> a_vectLayerNames);
		void destroy();

		//Layer name of default
		static constexpr char* LAYER_NAME_DEFAULT = "DEFAULT";
		//Layer id of default
		static const int LAYER_DEFAULT_ID = 0;

		static const Layer* GetLayerByName(const std::string& a_strLayerName);
		static const Layer* GetLayerByID(int a_iID);

		void printLayers();

		static T_LAYER_MAP_TYPE::const_iterator Begin()
		{
			return s_pInstance->m_layerMap.begin();
		}

		static T_LAYER_MAP_TYPE::const_iterator End()
		{
			return s_pInstance->m_layerMap.end();
		}
	};
}