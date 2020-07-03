#include <fretbuzz_pch.h>
#include "system_layer_stack.h"

namespace ns_fretBuzz
{
	//singleton
	SystemLayerStack* SystemLayerStack::s_pInstance = nullptr;

	SystemLayerStack::SystemLayerStack(int a_iStackSize)
	{
		m_vectLayers.reserve(a_iStackSize);
	}

	SystemLayerStack::~SystemLayerStack()
	{
		for (std::vector<SystemLayerBase*>::iterator l_Layer = m_vectLayers.begin();
			l_Layer != m_vectLayers.end(); l_Layer++)
		{
			SystemLayerBase*& l_pCurrent = *l_Layer;
			l_pCurrent->onDetached();
			delete l_pCurrent;
			l_pCurrent = nullptr;
		}
		m_vectLayers.clear();
	}

	SystemLayerStack* SystemLayerStack::Initialize(int a_iStackSize = 2)
	{
		if (s_pInstance != nullptr)
		{
			return nullptr;
		}
		s_pInstance = new SystemLayerStack(a_iStackSize);
		return s_pInstance;
	}

	void SystemLayerStack::destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	void SystemLayerStack::RemoveLayer(const std::string& a_strLayerName)
	{
		for (std::vector<SystemLayerBase*>::iterator l_Layer = s_pInstance->m_vectLayers.begin();
			l_Layer != s_pInstance->m_vectLayers.end(); l_Layer++)
		{
			if ((*l_Layer)->getName().compare(a_strLayerName))
			{
				SystemLayerBase*& l_pSystemLayer = (*l_Layer);
				l_pSystemLayer->onDetached();
				delete l_pSystemLayer;
				l_pSystemLayer = nullptr;
				s_pInstance->m_vectLayers.erase(l_Layer);
				break;
			}
		}
	}
}