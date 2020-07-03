#include <fretbuzz_pch.h>
#include "layer.h"
#include "layer_manager.h"

namespace ns_fretBuzz
{
	Layer::Layer()
		: Layer(LayerManager::LAYER_NAME_DEFAULT, LayerManager::LAYER_DEFAULT_ID)
	{
			
	}

	Layer::Layer(const std::string& a_strName)
		: Layer()
	{
		changeLayer(a_strName);
	}

	Layer::Layer(const std::string& a_strName, int a_iID)
		: m_strName{ a_strName },
		m_iID{ a_iID }
	{
	}

	void Layer::operator=(Layer a_Layer)
	{
		m_strName	= a_Layer.m_strName;
		m_iID		= a_Layer.m_iID;
	}

	void Layer::changeLayer(const std::string& a_strName)
	{
		const Layer* l_pLayer = LayerManager::GetLayerByName(a_strName);
		if (l_pLayer != nullptr)
		{
			*this = *l_pLayer;
		}
	}

	const std::string& Layer::getName() const
	{
		return m_strName;
	}

	int Layer::getID() const
	{
		return m_iID;
	}
}