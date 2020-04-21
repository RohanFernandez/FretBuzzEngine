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

		void Inspector::render(ns_system::SceneManager& a_SceneManager, int a_iFPS)
		{
			if (m_pSelectedGameObject == nullptr)
			{
				m_pSelectedGameObject = &a_SceneManager.getRootGameObject();
			}

			ImGui::Begin("EDITOR");

			ImGui::Text("FPS %d", a_iFPS);

			bool l_bIsPaused = ns_system::System::IsSystemPaused();
			ImGui::Checkbox("Pause", &l_bIsPaused);
			ns_system::System::ToggleSystemPause(l_bIsPaused);

			/*float l_fCurentScaledTime = ns_system::System::GetScaledTime();
			ImGui::SliderFloat("Scale Time", &l_fCurentScaledTime, 0.0f, 1.0f);
			ns_system::System::SetScaledTime(l_fCurentScaledTime);*/

			ImGui::Columns(2, "Hierarchy");

			a_SceneManager.editorHierarchyRender(m_pSelectedGameObject);

			ImGui::NextColumn();

			if (m_pSelectedGameObject != nullptr)
			{
				ImGui::Text("Selected : %s", m_pSelectedGameObject->getName().c_str());
				
				ImGui::BeginChild("Transform");
				ImGui::Text("FPS %d", a_iFPS);
				ImGui::EndChild();
			}

			ImGui::End();
		}
	}
}