#pragma once
#include "system_layer_base.h"
#include <editor/editor_inspector.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class EditorSystemLayer : public SystemLayerBase
		{
		private:
			ns_editor::Inspector* m_pInspector = nullptr;

		public:
			EditorSystemLayer();
			virtual ~EditorSystemLayer();

			void onAttach();
			void onDetach();

			virtual void render(SceneManager& a_SceneManager) override;
		};
	}
}