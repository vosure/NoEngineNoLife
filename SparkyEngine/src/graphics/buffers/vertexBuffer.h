#pragma once

#include "GL/glew.h"

namespace core {
	namespace graphics {

		class VertexBuffer
		{
		private:
			unsigned int m_BufferID;
			unsigned int m_ComponentsCount;

		public:
			//NOTE(vosure) Actually, "count" is not necessary, we can use sizeof(data) instead 
			VertexBuffer(float *data, unsigned int count, unsigned int componentsCount);
			~VertexBuffer();
			void bind() const;
			void unbind() const;

			inline unsigned int getComponentsCount() const { return m_ComponentsCount; }

		};

	}
}