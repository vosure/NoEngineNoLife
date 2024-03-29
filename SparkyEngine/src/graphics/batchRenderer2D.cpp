#include "batchRenderer2D.h"

namespace core {
	namespace graphics {

		BatchRenderer2D::BatchRenderer2D()
		{
			init();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_BufferData = (VertexData *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::submit(const Renderable2D *renderable)
		{
			const math::vec3 &position = renderable->getPosition();
			const math::vec2 &size = renderable->getSize();
			const math::vec4 &color = renderable->getColor();

			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;

			unsigned int unsigned_color = a << 24 | b << 16 | g << 8 | r;

			m_BufferData->vertex = *m_TransformationCache * position;
			m_BufferData->color = unsigned_color;
			m_BufferData++;

			m_BufferData->vertex = *m_TransformationCache * math::vec3(position.x, position.y + size.y, position.z);
			m_BufferData->color = unsigned_color;
			m_BufferData++;

			m_BufferData->vertex = *m_TransformationCache * math::vec3(position.x + size.x, position.y + size.y, position.z);
			m_BufferData->color = unsigned_color;
			m_BufferData++;

			m_BufferData->vertex = *m_TransformationCache * math::vec3(position.x + size.x, position.y, position.z);
			m_BufferData->color = unsigned_color;
			m_BufferData++;

			m_IndicesCount += 6;
		}

		void BatchRenderer2D::flush()
		{
			glBindVertexArray(m_VAO);
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES, m_IndicesCount, GL_UNSIGNED_INT, NULL);

			m_IBO->unbind();
			glBindVertexArray(0);

			m_IndicesCount = 0;
		}

		void BatchRenderer2D::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(ATTRIB_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (void *)0);
			glEnableVertexAttribArray(ATTRIB_VERTEX_INDEX);

			glVertexAttribPointer(ATTRIB_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (void *)(offsetof(VertexData, VertexData::color)));
			glEnableVertexAttribArray(ATTRIB_COLOR_INDEX);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			unsigned int *indices = new unsigned int[RENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				indices[i] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);
		}
	}
}