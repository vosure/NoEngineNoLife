#pragma once

#include "vertexArray.h"
namespace core {
	namespace graphics {

		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_ID);
		}

		VertexArray::~VertexArray()
		{
			for (int i = 0; i < m_Buffers.size(); i++)
			{
				delete m_Buffers[i];
			}

			glDeleteVertexArrays(1, &m_ID);
		}

		void VertexArray::addBuffer(VertexBuffer *buffer, unsigned int location)
		{
			bind();
			buffer->bind();

			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location, buffer->getComponentsCount(), GL_FLOAT, GL_FALSE, 0, (void *)0);

			buffer->unbind();
			unbind();
		}

		void VertexArray::bind() const
		{
			glBindVertexArray(m_ID);
		}

		void VertexArray::unbind() const
		{
			glBindVertexArray(0);
		}

	}
}