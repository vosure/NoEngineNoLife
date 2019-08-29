#pragma once

#include "GL/glew.h"

namespace core {
	namespace graphics {

		class IndexBuffer
		{
		private:
			unsigned int m_BufferID;
			unsigned int m_Count;

		public:
			//NOTE(vosure) Actually, "count" is not necessary, we can use sizeof(data) instead 
			IndexBuffer(unsigned short *indices, unsigned int count);
			IndexBuffer(unsigned int *indices, unsigned int count);
			~IndexBuffer();
			void bind() const;
			void unbind() const;

			inline unsigned int getCount() const { return m_Count; }
		};

	}
}