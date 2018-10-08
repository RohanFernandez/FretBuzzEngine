#pragma once
#include "../system/resource_container.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Light;
		class LightManager : public ResourceContainer<Light>
		{
		private:
			static LightManager* s_pInstance;

			LightManager();
			virtual ~LightManager();

		public:
			static LightManager* initialize();
			void destroy();
			static const LightManager* get();

			void registerLight(Light* a_pLight);
			static void s_registerLight(Light* a_pLight);

			void unregisterLight(Light* a_pLight);
			static void s_unregisterLight(Light* a_pLight);
		};
	}
}