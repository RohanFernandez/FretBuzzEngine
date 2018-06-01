#pragma once
#include <glew.h>
#include <glfw3.h>
#include <string>
#include "input.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Window
		{
		private:
			GLFWwindow* m_pGLFWwindow = nullptr;
			unsigned int m_uiWidth = 0;
			unsigned int m_uiHeight = 0;
			std::string m_strName;

			bool m_bIsInitialized = false;

			bool initialize();

			Input* m_pInput = nullptr;

			//Callback called on window closed
			static void OnWindowClose(GLFWwindow* a_pGLFWwindow);

			//Callback called on window resized
			static void OnWindowResize(GLFWwindow* a_pGLFWwindow, int a_iWidth, int a_iHeight);

		public:
			Window(unsigned int a_uiWidth, unsigned int a_uiHeight, const std::string a_strName);
			~Window();

			//Swaps the buffers, polls window events
			void update();

			//Clears the colors on the window
			void clear();

			//Checks if any gl errors exists
			void CheckForErrors();

			//Returns if window is closed
			bool isWindowClosed();

			//Returns true if the window succeeded
			//in its initalizing the GLFW and GLEW components
			inline bool isInitialized() const
			{
				return m_bIsInitialized;
			}

			//Returns the width of the window
			inline unsigned int getWidth() const
			{
				return m_uiWidth;
			}

			//Returns the height of the window
			inline unsigned int getHeight() const
			{
				return m_uiHeight;
			}
		};
	}
}
