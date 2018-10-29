#pragma once
#include "window.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		Window* Window::s_pInstance = nullptr;

		Window::Window(unsigned int a_uiWidth, unsigned int a_uiHeight, const std::string a_strName)
			: m_uiWidth{ a_uiWidth },
			m_uiHeight{ a_uiHeight },
			m_strName{ a_strName }
		{
			m_bIsInitialized = initialize();
		}

		Window* Window::initialize(unsigned int a_uiWidth, unsigned int a_uiHeight, const std::string a_strName)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "Window::initialize:: Window already exists.\n";
				return nullptr;
			}

			s_pInstance = new Window(a_uiWidth, a_uiHeight, a_strName);
			if (!s_pInstance->m_bIsInitialized)
			{
				s_pInstance->destroy();
			}

			return s_pInstance;
		}

		void Window::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}

		const Window* Window::get()
		{
			return s_pInstance;
		}

		bool Window::initialize()
		{
			if (!glfwInit())
			{
				std::cout << "Window::initialize:: Failed to initialize GLFW. \n";
				return false;
			}

			m_pGLFWwindow = glfwCreateWindow(m_uiWidth, m_uiHeight, m_strName.c_str(), nullptr, nullptr);
			if (m_pGLFWwindow == nullptr)
			{
				std::cout << "Window::initialize:: Failed to create GLFW window. \n";
				return false;
			}
			glfwMakeContextCurrent(m_pGLFWwindow);
			glfwSetWindowUserPointer(m_pGLFWwindow, this);

			glfwSetWindowCloseCallback(m_pGLFWwindow, OnWindowClose);
			glfwSetWindowSizeCallback(m_pGLFWwindow, OnWindowResize);

			glClearColor(0.0, 0.0, 0.0, 1.0);

			if (glewInit() != GLEW_OK)
			{
				std::cout << "Window::initialize:: Failed to initialize GLEW. \n";
				return false;
			}

			std::cout << "Window::initialize:: OpenGL version::" << glGetString(GL_VERSION) << "\n";

			CheckForErrors();

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_STENCIL_TEST);

			glViewport(0, 0, m_uiWidth, m_uiHeight);

			return true;
		}

		Window::~Window()
		{
			glfwTerminate();

			if (s_pInstance == this)
			{
				s_pInstance->m_vectWindowResizeCallbacks.clear();
				s_pInstance = nullptr;
			}
		}

		void Window::update()
		{
			CheckForErrors();
			glfwSwapBuffers(m_pGLFWwindow);
			glfwPollEvents();
		}

		void Window::clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		void Window::CheckForErrors()
		{
			GLenum l_error = glGetError();
			if (l_error != GLEW_NO_ERROR)
			{
				std::cout << "Window::CheckForErrors :: " << l_error << "\n";
			}
		}

		void Window::OnWindowClose(GLFWwindow* a_pGLFWwindow)
		{
			glfwSetWindowShouldClose(a_pGLFWwindow, GLFW_TRUE);
		}

		void Window::OnWindowResize(GLFWwindow* a_pGLFWwindow, int a_iWidth, int a_iHeight)
		{
			Window* l_pWindow = static_cast<Window*>(glfwGetWindowUserPointer(a_pGLFWwindow));
			l_pWindow->m_uiWidth = a_iWidth;
			l_pWindow->m_uiHeight = a_iHeight;
			glViewport(0, 0, a_iWidth, a_iHeight);

			l_pWindow->m_fAspectRatio = (float)a_iWidth / (float)a_iHeight;

			for (std::vector<WINDOW_RESIZE_TYPE>::iterator l_Iterator = l_pWindow->m_vectWindowResizeCallbacks.begin(),
				l_IteratorEnd = l_pWindow->m_vectWindowResizeCallbacks.end();
				l_Iterator != l_IteratorEnd; l_Iterator++)
			{
				(*l_Iterator)();
			}
		}

		bool Window::isWindowClosed() const
		{
			return glfwWindowShouldClose(m_pGLFWwindow);
		}

		void Window::closeWindow()
		{
			glfwSetWindowShouldClose(m_pGLFWwindow, GLFW_TRUE);
		}

		void Window::registerWindowResizeCallback(WINDOW_RESIZE_TYPE a_WindowResizeCallback)
		{
			if (s_pInstance != nullptr)
			{
				s_pInstance->m_vectWindowResizeCallbacks.emplace_back(a_WindowResizeCallback);
			}
		}

		void Window::unregisterWindowResizeCallback(WINDOW_RESIZE_TYPE a_WindowResizeCallback)
		{
			if (s_pInstance != nullptr)
			{
				for (std::vector<WINDOW_RESIZE_TYPE>::iterator l_Iterator = s_pInstance->m_vectWindowResizeCallbacks.begin(),
					l_IteratorEnd = s_pInstance->m_vectWindowResizeCallbacks.end();
					l_Iterator != l_IteratorEnd; 
					l_Iterator++)
				{
					if (*l_Iterator == a_WindowResizeCallback)
					{
						l_Iterator = s_pInstance->m_vectWindowResizeCallbacks.erase(l_Iterator);
						return;
					}
				}
			}
		}
	}
}