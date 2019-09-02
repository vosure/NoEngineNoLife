#pragma once

#include "GL/glew.h"
#include <vector>
#include "../math/math.h"

namespace core {
	namespace graphics {

		class Renderable2D;

		class Renderer2D
		{
		protected:
			std::vector<math::mat4> m_TransformationStack;
			const math::mat4 *m_TransformationCache;
		protected:
			Renderer2D()
			{
				m_TransformationStack.push_back(math::mat4::identitty());
				m_TransformationCache = &m_TransformationStack.back();
			}
		public:
			void push(const math::mat4 matrix, bool override = false)
			{
				if (override)
					m_TransformationStack.push_back(matrix);
				else
					m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

				m_TransformationCache = &m_TransformationStack.back();
			}

			void pop()
			{
				if (m_TransformationStack.size() > 1)
					m_TransformationStack.pop_back();

				m_TransformationCache = &m_TransformationStack.back();
			}

			virtual void begin() {}
			virtual void submit(const Renderable2D *renderable) = 0;
			virtual void end() {}
			virtual void flush() = 0;
		};

	}
}