#include "graphics/window.h"

#include <iostream>

int main()
{
	using namespace core::graphics;

	Window window(800, 600, "Hello Engine");

	while (!window.close())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glEnd();
		window.update();
	}

	return 0;
}