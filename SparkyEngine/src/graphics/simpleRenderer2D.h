#pragma once

#include "renderable2d.h"
#include "staticSprite.h"
#include <deque>

namespace core {
	namespace graphics {

		class SimpleRenderer2D : public Renderer2D
		{
		private :
			std::deque<const StaticSprite *> m_RenderQueue;
		public:
			void submit(const Renderable2D *renderable) override;
			void flush() override;
		};

	}
}