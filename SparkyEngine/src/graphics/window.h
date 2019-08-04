#pragma once

#include <iostream>

#include "GL/glew.h"

#include "GLFW/glfw3.h"

namespace core {
	namespace graphics {

#define MAX_KEYS  1024
#define MAX_MOUSE_BUTTONS 32	

		class Window
		{
		private:
			int m_Width, m_Height;
			const char *m_Tittle;
			GLFWwindow *m_Window;

			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_MOUSE_BUTTONS];
			double m_xPos, m_yPos;
		public:
			Window(int width, int height, const char *title);
			~Window();
			bool close();
			void update() const;

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void getCursorPosition(double &x, double &y) const;
		private:
			bool init();

			friend static void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
			friend static void mouse_cursor_callback(GLFWwindow *window, double xpos, double ypos);
		};

	}
}