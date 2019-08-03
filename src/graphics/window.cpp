#include "window.h"

namespace core {
	namespace graphics {

		void window_resize_callback(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		Window::Window(int width, int height, const char * tittle)
		{
			m_Width = width;
			m_Height = height;
			m_Tittle = tittle;
			if (!init())
			{
				glfwTerminate();
			}
			glClearColor(0.4f, 0.2f, 0.45f, 1.0f);
		}

		Window::~Window()
		{
			glfwTerminate();
			std::cout << "WIDNOW.H DESTRUCTOR" << std::endl;
		}

		bool Window::close()
		{
			return glfwWindowShouldClose(m_Window);
		}

		void Window::update() const
		{
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "ERRROR :: CANNOT INIT GLFW" << std::endl;
				return false;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Tittle, NULL, NULL);
			if (!m_Window)
			{
				std::cout << "ERRROR :: CANNOT CREATE WINDOW" << std::endl;
				return false;
			}

			glfwMakeContextCurrent(m_Window);
			glfwSetWindowSizeCallback(m_Window, window_resize_callback);

			return true;
		}

	}
}