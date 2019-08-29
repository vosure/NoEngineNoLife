#include "graphics/window.h"
#include "math/math.h"
#include "graphics/shader.h"

#include "graphics/buffers/indexBuffer.h"
#include "graphics/buffers/vertexBuffer.h"
#include "graphics/buffers/vertexArray.h"

#include "graphics/renderable2d.h"
#include "graphics/simpleRenderer2D.h"
#include "graphics/batchRenderer2D.h"
#include "graphics/sprite.h"
#include "graphics/staticSprite.h"

#include "graphics/layers/tileLayer.h"

#include "utils/timer.h"

#include <time.h>

#include <iostream>

#define BATCH_RENDERING 1

int main()
{
	using namespace core;
	using namespace graphics;
	using namespace math;

	Window window(800, 600, "Hello Engine");

	mat4 projection = mat4::orthographic(0, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("res/shaders/vertex.vert", "res/shaders/fragment.frag");
	Shader shader2("res/shaders/vertex.vert", "res/shaders/fragment.frag");

	TileLayer layer(&shader);
	
	for (float y = -9.0f; y < 9.0f; y += 1)
	{
		for (float x = -16.0f; x < 16.0f; x += 1)
		{
			float red = rand() % 1000 / 1000.0f;
			float green = rand() % 1000 / 1000.0f;
			float blue = rand() % 1000 / 1000.0f;
			layer.add(new Sprite(x, y, 0.5f, 0.5f, math::vec4(red, green, blue, 1.0f)));
		}
	}	

	TileLayer layer2(&shader2);
	layer2.add(new Sprite(-2, -2, 4, 4, vec4(1.0f, 0.0f, 0.8f, 1.0f)));

	Timer timer;
	float time = 0;
	unsigned int fps = 0;

	while (!window.close())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		double x, y;
		window.getCursorPosition(x, y);

		shader.bind();
		shader.setUniform2f("light_position", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		shader2.bind();
		shader2.setUniform2f("light_position", vec2(-3, -3));

		layer.render();
		layer2.render();
		window.update();
		
		fps++;
		if (timer.elapsed() - time > 1.0f)
		{
			time += 1.0f;
			printf("%d fps\n", fps);
			fps = 0;
		}
	}

	return 0;
}