#pragma once
#include <glfw3.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Input
		{
		private:

			enum KEY_STATE
			{
				KEY_RELEASED,
				KEY_PRESS,
				KEY_REPEAT
			};

			//singleton instance
			static Input* s_pInput;

			static constexpr int MAX_KEYBOARD_BTNS = 1024;
			static constexpr int MAX_MOUSE_BTNS = 32;

			KEY_STATE m_arrKeyCode[1024] = { KEY_RELEASED };
			KEY_STATE m_arrMouseCode[MAX_MOUSE_BTNS] = { KEY_RELEASED };

			double m_dMousePositionX = 0.0f;
			double m_dMousePositionY = 0.0f;

			//Sets the GLFW callbacks for key, mouse and pinter inputs.
			void SetInputCallbacks(GLFWwindow*& a_pGLFWwindow);

			//GLFW callback called on keyboard btn down
			static void OnKeyboardBtnPressed(GLFWwindow* a_pGLFWwindow, int a_iKey, int a_iScancode, int a_iAction, int a_iMods);

			//GLFW callback called on mouse btn down
			static void OnMouseBtnPressed(GLFWwindow* a_pFLFWwindow, int a_iButton, int a_iAction, int a_iMods);

			//GLFW gets the current mouse position
			static void OnGetCursorPosition(GLFWwindow* a_pGLFWwindow, double a_dPositionX, double a_dPositionY);

		public:
			Input(GLFWwindow* a_pGLFWWindow);
			~Input();

			//Returns mouse position
			static void GetMousePosition(double& a_dMouseX, double& a_dMouseY);

			//Checks if keyboard key with given keycode is down
			static bool IsKeyDown(const int a_iKeyCode);

			//Checks if mouse key with given keycode is down
			static bool IsMouseBtnDown(const int a_iMouseKeyCode);
		};
	}
}