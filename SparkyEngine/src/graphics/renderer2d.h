#pragma once

#include "renderable2d.h"
#include "GL/glew.h"

namespace core {
	namespace graphics {

		class Renderer2D
		{
		public:
			virtual void begin() {}
			virtual void end() {}
			virtual void submit(const Renderable2D *renderable) = 0;
			virtual void flush() = 0;
		};

	}
}