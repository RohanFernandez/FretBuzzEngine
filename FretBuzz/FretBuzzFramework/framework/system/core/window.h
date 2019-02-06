#pragma once
#include <glew.h>
#include <glfw3.h>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Window
		{
		private:
			//singleton instance
			static Window* s_pInstance;

			GLFWwindow* m_pGLFWwindow = nullptr;
			unsigned int m_uiWidth = 0;
			unsigned int m_uiHeight = 0;
			std::string m_strName;

			float m_fAspectRatio = 0.0f;

			bool m_bIsInitialized = false;

			bool initialize();

			//Callback called on window closed
			static void OnWindowClose(GLFWwindow* a_pGLFWwindow);

			//Callback called on window resized
			static void OnWindowResize(GLFWwindow* a_pGLFWwindow, int a_iWidth, int a_iHeight);

			using WINDOW_RESIZE_TYPE = void(*)();
			std::vector<WINDOW_RESIZE_TYPE> m_vectWindowResizeCallbacks;

			Window(unsigned int a_uiWidth, unsigned int a_uiHeight, const std::string a_strName);
			~Window();

		public:

			static Window* initialize(unsigned int a_uiWidth, unsigned int a_uiHeight, const std::string a_strName);
			void destroy();
			static const Window* get();

			//Swaps the buffers, polls window events
			void update();

			//Clears the colors on the window
			void clear();

			//Checks if any gl errors exists
			static void CheckForErrors();

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
			static inline unsigned int getWidth()
			{
				return s_pInstance->m_uiWidth;
			}

			//Returns the height of the window
			static inline unsigned int getHeight()
			{
				return s_pInstance->m_uiHeight;
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
				return s_pInstance->m_fAspectRatio;
			}

			static void registerWindowResizeCallback(WINDOW_RESIZE_TYPE a_WindowResizeCallback);
			static void unregisterWindowResizeCallback(WINDOW_RESIZE_TYPE a_WindowResizeCallback);
		};
	}
}
