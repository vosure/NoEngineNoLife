#pragma once

#include "layer.h"

namespace core {
	namespace graphics {

		Layer::Layer(Renderer2D * renderer, Shader * shader, math::mat4 projectionMatrix)
			:m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
		{
			m_Shader->bind();
			m_Shader->setUniformMat4("projection", projectionMatrix);
			m_Shader->unbind();
		}

		Layer::~Layer()
		{
			delete m_Shader;
			delete m_Renderer;

			for (int i = 0; i < m_Renderables.size(); i++)
			{
				delete m_Renderables[i];
			}
		}

		void Layer::add(Renderable2D *renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Layer::render()
		{
			m_Shader->bind();

			m_Renderer->begin();
			for (const Renderable2D *renderable : m_Renderables)
			{
				renderable->submit(m_Renderer);
			}
			m_Renderer->end();

			m_Renderer->flush();
		}
	}
}