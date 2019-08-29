#pragma once

#include "../renderer2d.h"

namespace core {
	namespace graphics {

		class Layer
		{
		protected:
			Renderer2D *m_Renderer;
			std::vector<Renderable2D *> m_Renderables;
			Shader *m_Shader;
			math::mat4 m_ProjectionMatrix;
		protected:
			Layer(Renderer2D *renderer, Shader *shader, math::mat4 projectionMatrix);
		public:
			virtual ~Layer();
			virtual void add(Renderable2D *renderable);
			void render();

		};

	}
}
