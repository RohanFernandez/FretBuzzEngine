#pragma once
#include "system_layer_base.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class GameSystemLayer : public SystemLayerBase
		{
		public:
			GameSystemLayer();
			virtual ~GameSystemLayer();

			virtual void update(const float& a_fDeltaTime, SceneManager& a_SceneManager) override;
			virtual void lateUpdate(const float& a_fDeltaTime, SceneManager& a_SceneManager) override;
			virtual void render(SceneManager& a_SceneManager) override;
		};
	}
}