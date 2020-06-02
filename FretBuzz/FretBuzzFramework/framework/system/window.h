#pragma once
#include <fretbuzz.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Viewport;
		class Window
		{
		public:
			//window resize callback type
			using WINDOW_RESIZE_TYPE = void(int, int);

		private:
			//singleton instance
			static Window* s_pInstance;

			GLFWwindow* m_pGLFWwindow = nullptr;
			int m_iWidth = 0;
			int m_iHeight = 0;
			std::string m_strName;

			bool m_bIsInitialized = false;

			bool initialize();

			//Callback called on window closed
			static void OnWindowClose(GLFWwindow* a_pGLFWwindow);

			//Callback called on window resized
			static void OnWindowResize(GLFWwindow* a_pGLFWwindow, int a_iWidth, int a_iHeight);

			Window(int a_iWidth, int a_iHeight, const std::string a_strName);
			~Window();

		public:
			static Window* initialize(int a_iWidth, int a_iHeight, const std::string a_strName);
			void destroy();
			static const Window* get();

			//Swaps the buffers, polls window events
			void update();

			//Clears the colors on the window
			void clear();

			//Checks if any gl errors exists
			static void ErrorCallback(int a_iErrorCode, const char* a_pDescription);

			//Returns if window is closed
			bool isWindowClosed() const;

			//Closes window by telling glfw to set the window open value.
			void closeWindow();

			//Returns true if the window succeeded
			//in its initalizing the GLFW and GLEW components
			inline bool isInitialized() const
			{
				return m_bIsInitialized;
			}

			//Returns the width of the window
			static inline int getWidth()
			{
				return s_pInstance->m_iWidth;
			}

			//Returns the height of the window
			static inline int getHeight()
			{
				return s_pInstance->m_iHeight;
			}

			//Changes the background color via OPEN GL
			inline void changeBackgroundColor(glm::vec4 a_vec4)
			{
				glClearColor(a_vec4.x, a_vec4.y, a_vec4.z, a_vec4.w);
			}

			//Returns the pointer to the glfw window
			inline GLFWwindow* getGLFWWindow()
			{
				return m_pGLFWwindow;
			}

			static float getAspectRatio()
			{
				return ((float)s_pInstance->getWidth()) / ((float)s_pInstance->getHeight());
			}

			void setViewport(const Viewport& a_Viewport) const;
		};
	}
}
