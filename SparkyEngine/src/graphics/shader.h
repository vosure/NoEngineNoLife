#pragma once

#include "GL/glew.h"

namespace core {
	namespace graphics {

		class Shader
		{
		private: 
			unsigned int m_ShaderID;
			const char *m_VertexPath;
			const char *m_FragmentPath;

		public:
			Shader(const char *vertexPath, const char *fragmentPath);
			~Shader();

			void bind() const;
			void unbind() const;

		private:
			unsigned int init();
		};

	}
}