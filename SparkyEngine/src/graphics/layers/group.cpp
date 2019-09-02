#include "group.h"

namespace core {
	namespace graphics {

		Group::Group(const math::mat4 & matrix)
			:m_TransformationMatrix(matrix)
		{
		}

		void Group::add(Renderable2D * renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Group::submit(Renderer2D * renderer) const
		{
			renderer->push(m_TransformationMatrix);

			for (const Renderable2D *renderable : m_Renderables)
				renderable->submit(renderer);

			renderer->pop();
		}

	}
}