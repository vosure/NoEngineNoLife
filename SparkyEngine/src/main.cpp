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
#include "graphics/layers/group.h"

#include "utils/timer.h"

#include <time.h>

#include <iostream>

#define BATCH_RENDERING 1
#define TEST_50K_SPRITES 0

int main()
{
	using namespace core;
	using namespace graphics;
	using namespace math;

	Window window(800, 600, "Hello Engine");

	mat4 projection = mat4::orthographic(0, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("res/shaders/vertex.vert", "res/shaders/fragment.frag");
	Shader shader2("res/shaders/vertex.vert", "res/shaders/fragment.frag");
	shader.bind();
	shader2.bind();
	shader.setUniform2f("light_position", vec2(4.0f, 1.5f));
	shader2.setUniform2f("light_position", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);
	
#if TEST_50K_SPRITES
	for (float y = -9.0f; y < 9.0f; y += 0.1)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1)
		{
			layer.add(new Sprite(x, y, 0.09f, 0.09f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}
#else

	Group* group = new Group(mat4::translation(math::vec3(-15.0f, 5.0f, 0.0f)));
	group->add(new Sprite(0, 0, 6, 3, math::vec4(1, 1, 1, 1)));

	Group* button = new Group(mat4::translation(vec3(0.5f, 0.5f, 0.0f)));
	button->add(new Sprite(0, 0, 5.0f, 2.0f, math::vec4(1, 0, 1, 1)));
	button->add(new Sprite(0.5f, 0.5f, 3.0f, 1.0f, math::vec4(0.2f, 0.3f, 0.8f, 1)));
	group->add(button);

	layer.add(group);

#endif

	TileLayer layer2(&shader2);
	layer2.add(new Sprite(-2, -2, 4, 4, math::vec4(1, 0, 1, 1)));

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
		//shader2.setUniform2f("light_position", vec2(0, 0));

		layer.render();
		//layer2.render();
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