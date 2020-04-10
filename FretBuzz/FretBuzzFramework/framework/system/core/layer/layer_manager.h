#pragma once
#include <bitset>
#include "layer.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class FRETBUZZ_API LayerManager
		{
		private:

			//singleton instance
			static LayerManager* s_pInstance;

			using T_LAYER_MAP_TYPE = std::unordered_map<std::string, Layer>;
			T_LAYER_MAP_TYPE m_layerMap;

			LayerManager(std::vector<std::string> a_vectLayerNames);
			~LayerManager();

			bool addLayer(std::string a_strLayerName, int a_iLayerIndex);

		public:
			static LayerManager* initialize(std::vector<std::string> a_vectLayerNames);
			void destroy();

			//Layer name of default
			static const std::string LAYER_NAME_DEFAULT;
			//Layer id of default
			static const int LAYER_DEFAULT_ID = 0;

			static const Layer* getLayerIdByName(std::string a_strLayerName);

			void printLayers();
		};
	}
}