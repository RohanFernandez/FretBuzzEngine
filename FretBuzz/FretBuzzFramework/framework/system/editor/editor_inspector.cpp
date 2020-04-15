#include <fretbuzz_pch.h>
#include "editor_inspector.h"
#include <imgui/imgui.h>
#include <system/core/system.h>

namespace ns_fretBuzz
{
	namespace ns_editor
	{
		//singleton instance
		Inspector* Inspector::s_pInstance = nullptr;

		int printThis4(int)
		{
			std::cout << "Printing 444 ... global func\n";
			return 0;
		}

		Inspector::Inspector()
		{
		}

		Inspector::~Inspector()
		{
		
		}

		Inspector* Inspector::initialize()
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "ResourceManager::initialize:: ResourceManager already exists.\n";
				return nullptr;
			}
			s_pInstance = new Inspector();
			return s_pInstance;
		}

		void Inspector::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}

		void Inspector::render(int a_iFPS)
		{
			ImGui::Begin("System Manager");

			ImGui::Text("FPS %d", a_iFPS);

			bool l_bIsPaused = ns_system::System::IsSystemPaused();
			ImGui::Checkbox("Pause", &l_bIsPaused);
			ns_system::System::ToggleSystemPause(l_bIsPaused);

			float l_fCurentScaledTime = ns_system::System::GetScaledTime();
			ImGui::SliderFloat("Scale Time", &l_fCurentScaledTime, 0.0f, 1.0f);
			ns_system::System::SetScaledTime(l_fCurentScaledTime);

			ImGui::End();
		}
	}
}