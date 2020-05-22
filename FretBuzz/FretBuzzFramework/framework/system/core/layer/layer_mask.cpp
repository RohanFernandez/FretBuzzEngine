#include <fretbuzz_pch.h>
#include "layer_manager.h"
#include "layer_mask.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		LayerMask::LayerMask(const LayerMask& a_LayerMask)
		{
			m_Bits = a_LayerMask.m_Bits;
		}

		LayerMask::LayerMask(PREDEFINED_MASK a_PredefinedMask)
		{
			setPredefined(a_PredefinedMask);
		}

		LayerMask::LayerMask()
			:LayerMask(std::vector<std::string>({ LayerManager::LAYER_NAME_DEFAULT }))
		{
		
		}

		LayerMask::LayerMask(std::vector<std::string> a_vectLayers)
		{
			addLayers(a_vectLayers);
		}

		void LayerMask::setPredefined(PREDEFINED_MASK a_PredefinedMask)
		{
			if (a_PredefinedMask == PREDEFINED_MASK::NONE)
			{
				m_Bits.reset();
			}
			else //PREDEFINED_MASK::EVERYTHING
			{
				m_Bits.set();
			}
		}

		void LayerMask::addLayer(std::string a_strLayerName) 
		{
			const Layer* l_pLayer = LayerManager::GetLayerIdByName(a_strLayerName);
			if (l_pLayer != nullptr)
			{
				addLayer(*l_pLayer);
			}
		}

		void LayerMask::addLayer(const Layer& a_Layer)
		{
			m_Bits.set(a_Layer.getID());
		}

		void LayerMask::addLayers(std::vector<std::string> a_vectLayers)
		{
			size_t l_iLayerCount = a_vectLayers.size();
			for (size_t l_iLayerIndex = 0; l_iLayerIndex < l_iLayerCount; l_iLayerIndex++)
			{
				addLayer(a_vectLayers[l_iLayerIndex]);
			}
		}

		void LayerMask::removeLayer(std::string a_strLayerName) 
		{
			const Layer* l_pLayer = LayerManager::GetLayerIdByName(a_strLayerName);
			if (l_pLayer != nullptr)
			{
				removeLayer(*l_pLayer);
			}
		}

		void LayerMask::removeLayer(const Layer& a_Layer)
		{
			m_Bits.reset(a_Layer.getID());
		}

		void LayerMask::removeLayers(std::vector<std::string> a_vectLayers)
		{
			size_t l_iLayerCount = a_vectLayers.size();
			for (size_t l_iLayerIndex = 0; l_iLayerIndex < l_iLayerCount; l_iLayerIndex++)
			{
				removeLayer(a_vectLayers[l_iLayerIndex]);
			}
		}

		bool LayerMask::isLayerInMask(const std::string& a_strLayerName) const
		{
			const Layer* l_pLayer = LayerManager::GetLayerIdByName(a_strLayerName);
			return  l_pLayer == nullptr ? false : isLayerInMask(*l_pLayer);
		}

		bool LayerMask::isLayerInMask(const Layer& a_Layer) const
		{
			return m_Bits.test(a_Layer.getID());
		}

		void LayerMask::operator=(const LayerMask& a_LayerMask)
		{
			m_Bits = a_LayerMask.m_Bits;
		}
	}
}