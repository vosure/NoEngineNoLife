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
	shader.bind();
	shader.setUniformMat4("projection", projection);

	std::vector<Renderable2D *> sprites;

	srand(time(NULL));

#if BATCH_RENDERING
	for (float y = 0; y < 9.0f; y+=0.1)
	{
		for (float x = 0; x < 16.0f; x += 0.1)
		{
			float red = rand() % 1000 / 1000.0f;
			float green = rand() % 1000 / 1000.0f;
			float blue = rand() % 1000 / 1000.0f;
			sprites.push_back(new Sprite(x, y, 0.4f, 0.4f, math::vec4(red, green, blue, 1.0f)));
		}
	}
	BatchRenderer2D renderer;
#else
	for (float y = 0; y < 9.0f; y+=0.2)
	{
		for (float x = 0; x < 16.0f; x+=0.2)
		{
			float red = rand() % 1000 / 1000.0f;
			float green = rand() % 1000 / 1000.0f;
			float blue = rand() % 1000 / 1000.0f;
			sprites.push_back(new StaticSprite(x, y, 1.0f, 1.0f, math::vec4(red, green, blue, 1.0f), shader));
		}
	}
	SimpleRenderer2D renderer;
#endif

	Timer timer;
	float time = 0;
	unsigned int fps = 0;

	while (!window.close())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		double x, y;
		window.getCursorPosition(x, y);
		shader.setUniform2f("light_position", vec2((float)(x * 16.0f / 800.0f), (float)(9.0f - y * 9.0f / 600.0f)));

		//mat4 model = mat4::rotation(timer.elapsed() * 100.0f, vec3(0.0f, 1.0f, 1.0f));
		//shader.setUniformMat4("model", model);


#if BATCH_RENDERING
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
#if BATCH_RENDERING
		renderer.end();
#endif
		renderer.flush();

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