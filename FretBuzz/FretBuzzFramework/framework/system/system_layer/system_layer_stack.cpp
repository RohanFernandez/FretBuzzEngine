#include <fretbuzz_pch.h>
#include "system_layer_stack.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//singleton
		SystemLayerStack* SystemLayerStack::s_pInstance = nullptr;

		SystemLayerStack::SystemLayerStack()
		{
		
		}

		SystemLayerStack::~SystemLayerStack()
		{
		
		}

		SystemLayerStack* SystemLayerStack::Initialize()
		{
			if (s_pInstance != nullptr)
			{
				return nullptr;
			}
			s_pInstance = new SystemLayerStack();
			return s_pInstance;
		}

		void SystemLayerStack::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}
}