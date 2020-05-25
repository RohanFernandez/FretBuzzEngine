#pragma once
#include <bitset>
#include "layer.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class  LayerManager
		{
		private:

			//singleton instance
			static LayerManager* s_pInstance;

			using T_LAYER_MAP_TYPE = std::unordered_map<std::string, Layer>;
			T_LAYER_MAP_TYPE m_layerMap;

			LayerManager(std::vector<std::string> a_vectLayerNames);
			~LayerManager();

			bool addLayer(std::string a_strLayerName, int a_iLayerIndex);
			Layer* getLayerIdByName(std::string a_strLayerName);

		public:
			static LayerManager* initialize(std::vector<std::string> a_vectLayerNames);
			void destroy();

			//Layer name of default
			static constexpr char* LAYER_NAME_DEFAULT = "DEFAULT";
			//Layer id of default
			static const int LAYER_DEFAULT_ID = 0;

			static const Layer* GetLayerIdByName(std::string a_strLayerName);

			void printLayers();
		};
	}
}