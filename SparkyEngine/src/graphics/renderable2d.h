#pragma once

#include "buffers/indexBuffer.h"
#include "buffers/vertexBuffer.h"
#include "buffers/vertexArray.h"

#include "shader.h"

#include "../math/math.h"

namespace core {
	namespace graphics {

		class Renderable2D
		{
		protected:
			math::vec3 m_Position;
			math::vec2 m_Size;
			math::vec4 m_Color;

			VertexArray *m_VertexArray;
			IndexBuffer *m_IndexBuffer;
			Shader &m_Shader;

		public:
			Renderable2D(math::vec3 position, math::vec2 size, math::vec4 color, Shader &shader)
				:m_Position(position), m_Size(size), m_Color(color), m_Shader(shader)
			{
				m_VertexArray = new VertexArray();

				float positions[] =
				{
					0.0f,		0.0f,	0.0f,
					0.0f,		size.y, 0.0f,
					size.x,		size.y, 0.0f,
					size.x,		0.0f,	0.0f
				};

				float colors[] =
				{
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
				};

				m_VertexArray->addBuffer(new VertexBuffer(positions, 4 * 3, 3), 0);
				m_VertexArray->addBuffer(new VertexBuffer(colors, 4 * 4, 4), 1);

				unsigned short indices[] = { 0, 1, 2, 2, 3, 0 };
				m_IndexBuffer = new IndexBuffer(indices, 6);
			}

			virtual ~Renderable2D()
			{
				delete m_VertexArray;
				delete m_IndexBuffer;
			}

			inline const VertexArray *getVAO() const { return m_VertexArray; }
			inline const IndexBuffer *getIBO() const { return m_IndexBuffer; }

			inline	Shader &getShader() const { return m_Shader; }

			inline const math::vec3 &getPosition() const { return m_Position; }
			inline const math::vec2 &getSize() const { return m_Size; }
			inline const math::vec4 &getColor() const { return m_Color; }
		};

	}
}