#pragma once
#include "layer.h"
#include <vector>
#include <bitset>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class  LayerMask
		{
		public:
			enum class PREDEFINED_MASK
			{
				NONE		=	0,
				EVERYTHING	=	1
			};

		private:
			std::bitset<Layer::MAX_CAPACITY_LAYERS> m_Bits;

		public:
			LayerMask(const LayerMask& a_LayerMask);
			LayerMask(PREDEFINED_MASK a_PredefinedMask);
			LayerMask(std::vector<std::string> a_vectLayers);
			LayerMask();

			void setPredefined(PREDEFINED_MASK a_PredefinedMask);

			void addLayer(std::string a_strLayerName);
			void addLayer(const Layer& a_Layer);
			void addLayers(std::vector<std::string> a_vectLayers);

			void removeLayer(std::string a_strLayerName);
			void removeLayer(const Layer& a_Layer);
			void removeLayers(std::vector<std::string> a_vectLayers);

			bool isLayerInMask(const std::string& a_strLayerName) const;
			bool isLayerInMask(const Layer& a_Layer) const;

			void operator=(const LayerMask& a_LayerMask);
		};
	}
}