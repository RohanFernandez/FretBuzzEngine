#pragma once
#include "utils/Event/Delegate/delegate.h"
#include "system/scene_manager.h"

namespace ns_fretBuzz
{
	namespace ns_editor
	{
		class  Inspector
		{
		private:
			static Inspector* s_pInstance;

			ns_system::GameObject* m_pSelectedGameObject = nullptr;

			Inspector();
			~Inspector();

		public:
			static Inspector* initialize();
			void destroy();
			void render(ns_system::SceneManager& a_SceneManager, int a_iFPS);
		};
	}
}