#pragma once

#include "GLFW/glfw3.h"
#include <iostream>

namespace core {
	namespace graphics {

		class Window
		{
		private:
			int m_Width, m_Height;
			const char *m_Tittle;
			GLFWwindow *m_Window;
		public:
			Window(int width, int height, const char *title);
			~Window();
			bool close();
			void update() const;
		private:
			bool init();
		};

	}
}