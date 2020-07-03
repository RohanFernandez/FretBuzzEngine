#include <fretbuzz_pch.h>
#include "window.h"
#include "components/viewport.h"
#include <fretbuzz.h>

namespace ns_fretBuzz
{
	//singleton instance
	Window* Window::s_pInstance = nullptr;

	Window::Window(int a_iWidth, int a_iHeight, const std::string a_strName)
		: m_iWidth{ a_iWidth },
		m_iHeight{ a_iHeight },
		m_strName{ a_strName }
	{
		m_bIsInitialized = initialize();
	}

	Window* Window::initialize(int a_uiWidth, int a_uiHeight, const std::string a_strName)
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
		glfwSetErrorCallback(ErrorCallback);
		if (!glfwInit())
		{
			std::cout << "Window::initialize:: Failed to initialize GLFW. \n";
			return false;
		}
		m_pGLFWwindow = glfwCreateWindow(m_iWidth, m_iHeight, m_strName.c_str(), nullptr, nullptr);
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


		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);

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
		glfwSwapBuffers(m_pGLFWwindow);
		glfwPollEvents();
	}

	void Window::clear()
	{
		glDisable(GL_SCISSOR_TEST);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glEnable(GL_SCISSOR_TEST);
	}

	void Window::ErrorCallback(int a_iErrorCode, const char* a_pDescription)
	{
		ENGINE_ERROR("WINDOW ERROR:		{0} : {1}", a_iErrorCode, a_pDescription);
	}

	void Window::OnWindowClose(GLFWwindow* a_pGLFWwindow)
	{
		glfwSetWindowShouldClose(a_pGLFWwindow, GLFW_TRUE);
	}

	void Window::OnWindowResize(GLFWwindow* a_pGLFWwindow, int a_iWidth, int a_iHeight)
	{
		Window* l_pWindow = static_cast<Window*>(glfwGetWindowUserPointer(a_pGLFWwindow));
		l_pWindow->m_iWidth = a_iWidth;
		l_pWindow->m_iHeight = a_iHeight;

		EventManager::Invoke<WINDOW_RESIZE_TYPE>(FRETBUZZ_ON_WINDOW_RESIZE, a_iWidth, a_iHeight);
	}

	bool Window::isWindowClosed() const
	{
		return glfwWindowShouldClose(m_pGLFWwindow);
	}

	void Window::closeWindow()
	{
		glfwSetWindowShouldClose(m_pGLFWwindow, GLFW_TRUE);
	}

	void Window::setViewport(const Viewport& a_Viewport) const
	{
		const glm::vec2 l_v2OriginXY = a_Viewport.getOriginXY();
		const glm::vec2 l_v2DimensionWH = a_Viewport.getDimensionWH();
		glViewport(l_v2OriginXY.x, l_v2OriginXY.y, l_v2DimensionWH.x, l_v2DimensionWH.y);
		glScissor(l_v2OriginXY.x, l_v2OriginXY.y, l_v2DimensionWH.x, l_v2DimensionWH.y);
	}
}