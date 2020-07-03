#pragma once
#include <Event/delegate.h>
#include "system/scene_manager.h"

namespace ns_fretBuzz
{
	class  Inspector
	{
	private:
		static Inspector* s_pInstance;

		GameObject* m_pSelectedGameObject = nullptr;

		Inspector();
		~Inspector();

	public:
		static Inspector* initialize();
		void destroy();
		void render(SceneManager& a_SceneManager);
	};
}