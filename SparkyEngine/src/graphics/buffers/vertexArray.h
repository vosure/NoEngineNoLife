#pragma once

#include "vertexBuffer.h"
#include <vector>


namespace core {
	namespace graphics {

		class VertexArray
		{
		private:
			unsigned int m_ID;
			std::vector<VertexBuffer *> m_Buffers;

		public:
			VertexArray();
			~VertexArray();

			void addBuffer(VertexBuffer *buffer, unsigned int location);
			void bind() const;
			void unbind() const;
		};

	}
}
