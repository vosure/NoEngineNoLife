#include "graphics/window.h"
#include "math/vec2.h"
#include "math/vec4.h"

#include <iostream>

int main()
{
	using namespace core;
	using namespace graphics;
	using namespace math;


	Window window(800, 600, "Hello Engine");
	double x, y;
	while (!window.close())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		window.getCursorPosition(x, y);

		///test math
		std::cout << vec4(1.0f, 4.0f, 1.0f, 4.0f).multiply(vec4(2.0f, 5.0f, 1.0f, 4.0f)) << std::endl;

		if (window.isKeyPressed( GLFW_KEY_D))
			std::cout << "KEY PRESSED" << std::endl;

		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1 ))
			std::cout << "MOUSE BUTTON PRESSED" << std::endl;
		
		std::cout << x << "|" << y << std::endl;

		window.update();
	}

	return 0;
}