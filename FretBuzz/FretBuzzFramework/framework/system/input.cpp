#pragma once
#include "input.h"
#include <cassert>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		Input* Input::s_pInput = nullptr;

		Input::Input(GLFWwindow* a_pGLFWWindow)
		{
			if (s_pInput == nullptr)
			{
				s_pInput = this;
				m_pGLFWWindowRef = a_pGLFWWindow;
				SetInputCallbacks(a_pGLFWWindow);
			}
		}

		Input::~Input()
		{
			if (s_pInput == this)
			{
				m_pGLFWWindowRef = nullptr;
				s_pInput = nullptr;
			}
		}

		void Input::SetInputCallbacks(GLFWwindow*& a_pGLFWwindow)
		{
			glfwSetCursorPosCallback(a_pGLFWwindow, OnGetCursorPosition);
			glfwSetKeyCallback(a_pGLFWwindow, OnKeyboardBtnPressed);
			glfwSetMouseButtonCallback(a_pGLFWwindow, OnMouseBtnPressed);
		}

		void Input::OnKeyboardBtnPressed(GLFWwindow* a_pGLFWwindow, int a_iKey, int a_iScancode, int a_iAction, int a_iMods)
		{
			s_pInput->m_arrKeyCode[a_iKey] = (KEY_STATE)a_iAction;
		}

		void Input::OnMouseBtnPressed(GLFWwindow* a_pFLFWwindow, int a_iButton, int a_iAction, int a_iMods)
		{
			s_pInput->m_arrMouseCode[a_iButton] = (KEY_STATE)a_iAction;
		}

		void Input::OnGetCursorPosition(GLFWwindow* a_pGLFWwindow, double a_dPositionX, double a_dPositionY)
		{
			s_pInput->m_dMousePositionX = a_dPositionX;
			s_pInput->m_dMousePositionY = a_dPositionY;
		}

		void Input::GetMousePosition(double& a_dMouseX, double& a_dMouseY)
		{
			a_dMouseX = s_pInput->m_dMousePositionX;
			a_dMouseY = s_pInput->m_dMousePositionY;
		}

		bool Input::IsKeyDown(const int a_iKeyCode)
		{
			assert(a_iKeyCode < MAX_KEYBOARD_BTNS && "KeyCode is more than max keyboard keys");
			return s_pInput->m_arrKeyCode[a_iKeyCode] != KEY_RELEASED;
		}

		bool Input::IsMouseBtnDown(const int a_iMouseKeyCode)
		{
			assert(a_iMouseKeyCode < MAX_MOUSE_BTNS && "KeyCode is more than max mouse buttons");
			return s_pInput->m_arrMouseCode[a_iMouseKeyCode] != KEY_RELEASED;
		}

		void Input::setCursorEnability(bool a_bIsEnabled, bool a_bIsCursorVisible)
		{
			glfwSetInputMode(s_pInput->m_pGLFWWindowRef, GLFW_CURSOR, a_bIsEnabled ? (a_bIsCursorVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN): GLFW_CURSOR_DISABLED);
		}
	}
}