#include <fretbuzz_pch.h>
#include "editor_system_layer.h"
#include <window.h>
#include <imgui/imgui.h>
#include <examples/imgui_impl_glfw.cpp>
#include <examples/imgui_impl_opengl3.cpp>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		EditorSystemLayer::EditorSystemLayer()
			: SystemLayerBase("EDITOR")
		{
			m_pInspector = ns_editor::Inspector::initialize();
		}

		EditorSystemLayer::~EditorSystemLayer()
		{
			m_pInspector->destroy();
			m_pInspector = nullptr;
		}

		void EditorSystemLayer::onAttach()
		{
			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

			ImGui::StyleColorsDark();

			// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}

			ImGui_ImplGlfw_InitForOpenGL(ns_graphics::Window::GetWindow().getGLFWWindow(), true);
			ImGui_ImplOpenGL3_Init("#version 410");
		}

		void EditorSystemLayer::onDetach()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
		}

		void EditorSystemLayer::render(SceneManager& a_SceneManager)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			m_pInspector->render(a_SceneManager);

			ImGuiIO& io = ImGui::GetIO();
			io.DisplaySize = ImVec2((float)ns_graphics::Window::getWidth(), (float)ns_graphics::Window::getHeight());

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
		}
	}
}