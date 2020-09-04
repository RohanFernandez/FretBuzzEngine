#pragma once
#include "layer.h"
#include <vector>
#include <bitset>

namespace FRETBUZZ
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

		bool addLayer(std::string a_strLayerName);
		void addLayer(const Layer& a_Layer);
		void addLayers(std::vector<std::string> a_vectLayers);

		bool removeLayer(std::string a_strLayerName);
		bool removeLayer(const Layer& a_Layer);
		void removeLayers(std::vector<std::string> a_vectLayers);

		bool isLayerInMask(const std::string& a_strLayerName) const;
		bool isLayerInMask(const Layer& a_Layer) const;
		bool isLayerInMask(const int& a_iID) const;

		void operator=(const LayerMask& a_LayerMask);

		int getBitfield();
		size_t getLayersCount();
		const std::bitset<Layer::MAX_CAPACITY_LAYERS>& getBitset();
	};
}