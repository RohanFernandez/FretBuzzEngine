#pragma once
#include "system_layer_base.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class SystemLayerStack
		{
		private:
			//singleton
			static SystemLayerStack* s_pInstance;

			SystemLayerStack();
			~SystemLayerStack();

			std::vector<SystemLayerBase*> m_vectLayers;

		public:
			static SystemLayerStack* Initialize();
			void destroy();
		};
	}
}