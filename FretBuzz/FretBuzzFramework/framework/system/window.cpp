#pragma once
#include "window.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//singleton instance
		Window* Window::s_pInstance = nullptr;

		Window::Window(unsigned int a_uiWidth, unsigned int a_uiHeight, const std::string a_strName)
			: m_uiWidth{a_uiWidth},
			  m_uiHeight{ a_uiHeight },
			  m_strName{ a_strName }
		{
			if (s_pInstance != nullptr)
			{
				return;
			}
			m_bIsInitialized = initialize();

			if (m_bIsInitialized)
			{
				s_pInstance = this;
			}
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

			glClearColor(1.0, 0.0, 0.0, 1.0);

			if (glewInit() != GLEW_OK)
			{
				std::cout<< "Window::initialize:: Failed to initialize GLEW. \n";
				return false;
			}
			
			std::cout<< "Window::initialize:: OpenGL version::"<< glGetString(GL_VERSION)<<"\n";

			CheckForErrors();

			glEnable(GL_DEPTH_TEST);
			glViewport(0, 0, m_uiWidth, m_uiHeight);

			return true;
		}

		Window::~Window()
		{
			glfwTerminate();

			if (s_pInstance == this)
			{
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
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::CheckForErrors()
		{
			GLenum l_error = glGetError();
			if (l_error != GLEW_NO_ERROR)
			{
				std::cout << "Window::CheckForErrors :: " <<l_error << "\n";
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
		}

		bool Window::isWindowClosed()
		{
			return glfwWindowShouldClose(m_pGLFWwindow);
		}
	}
}