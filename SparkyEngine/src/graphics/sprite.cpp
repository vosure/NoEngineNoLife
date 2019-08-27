#pragma once

#include "sprite.h"

namespace core {
	namespace graphics {
		Sprite::Sprite(float x, float y, float width, float height, const math::vec4 & color)
			:Renderable2D(math::vec3(x, y, 0), math::vec2(width, height), color)
		{
		}
	}
}