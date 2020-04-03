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
			fuzzDele.Add<doClass, &doClass::printThis1>(&testDoClass);
			fuzzDele.Add<doClass, &doClass::printThis2>(&testDoClass);
			fuzzDele.Add<&doClass::printThis3>();
			fuzzDele.Add <&printThis4>();
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

			std::string l_strFPS = "FPS : " + std::to_string(a_iFPS);
			ImGui::Text(l_strFPS.c_str());

			bool l_bIsPaused = ns_system::System::IsSystemPaused();
			ImGui::Checkbox("Pause", &l_bIsPaused);
			ns_system::System::ToggleSystemPause(l_bIsPaused);

			float l_fCurentScaledTime = ns_system::System::GetScaledTime();
			ImGui::SliderFloat("Scale Time", &l_fCurentScaledTime, 0.0f, 1.0f);
			ns_system::System::SetScaledTime(l_fCurentScaledTime);

			if(ImGui::Button("Delegate Test", { 10.0f, 5.0f }))
			{
				fuzzDele(6);

				m_iActionRemoveCount++;

				if (m_iActionRemoveCount == 1)
				{
					std::cout << "1\n";
					fuzzDele.Remove<&printThis4>();
				}
				else if (m_iActionRemoveCount == 2)
				{
					std::cout << "2\n";
					fuzzDele.Remove<&doClass::printThis3>();
				}
				else if (m_iActionRemoveCount == 3)
				{
					std::cout << "3\n";
					fuzzDele.Remove<doClass, &doClass::printThis2>(&testDoClass);
				}
				else if (m_iActionRemoveCount == 4)
				{
					std::cout << "4\n";
					fuzzDele.Remove<doClass, &doClass::printThis1>(&testDoClass);
				}
			}

			ImGui::End();
		}
	}
}