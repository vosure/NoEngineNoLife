#include "simpleRenderer2D.h"
#pragma once

namespace core {
	namespace graphics {

		void SimpleRenderer2D::submit(const Renderable2D  *renderable)
		{
			m_RenderQueue.push_back((StaticSprite *)renderable);
		}

		void SimpleRenderer2D::flush()
		{
			while (!m_RenderQueue.empty())
			{
				const StaticSprite *sprite = m_RenderQueue.front();

				sprite->getVertexArray()->bind();
				sprite->getIndexBuffer()->bind();

				sprite->getShader().setUniformMat4("model", math::mat4::translation(sprite->getPosition()));
				glDrawElements(GL_TRIANGLES, sprite->getIndexBuffer()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				sprite->getIndexBuffer()->unbind();
				sprite->getVertexArray()->unbind();

				m_RenderQueue.pop_front();
			}
		}

	}
}
