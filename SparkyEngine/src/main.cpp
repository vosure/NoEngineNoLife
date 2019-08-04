#include "graphics/window.h"

#include <iostream>

int main()
{
	using namespace core::graphics;

	Window window(800, 600, "Hello Engine");
	double x, y;
	while (!window.close())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		window.getCursorPosition(x, y);

		if (window.isKeyPressed( GLFW_KEY_D))
			std::cout << "KEY PRESSED" << std::endl;

		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1 ))
			std::cout << "MOUSE BUTTON PRESSED" << std::endl;

		std::cout << x << "|" << y << std::endl;

		window.update();
	}

	return 0;
}