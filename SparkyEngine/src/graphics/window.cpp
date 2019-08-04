#include "window.h"

namespace core {
	namespace graphics {

		void window_resize_callback(GLFWwindow *window, int width, int height);
		void keyboard_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
		void mouse_cursor_callback(GLFWwindow * window, double xpos, double ypos);

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

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}
			for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
			}
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

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			return m_MouseButtons[button];
		}

		void Window::getCursorPosition(double & x, double & y) const
		{
			x = m_xPos;
			y = m_yPos;
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

			glfwSetWindowUserPointer(m_Window, this);

			glfwSetWindowSizeCallback(m_Window, window_resize_callback);
			glfwSetKeyCallback(m_Window, keyboard_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, mouse_cursor_callback);

			if (glewInit() != GLEW_OK)
			{
				std::cout << "CANNOT INITIALIZE GLEW" << std::endl;
				return false;
			}

			return true;
		}

		void window_resize_callback(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void keyboard_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			Window *targetWindow = (Window *)glfwGetWindowUserPointer(window);
			targetWindow->m_Keys[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
		{
			Window *targetWindow = (Window *)glfwGetWindowUserPointer(window);
			targetWindow->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		void mouse_cursor_callback(GLFWwindow * window, double xpos, double ypos)
		{
			Window *targetWindow = (Window *)glfwGetWindowUserPointer(window);
			targetWindow->m_xPos = xpos;
			targetWindow->m_yPos = ypos;
		}

	}
}