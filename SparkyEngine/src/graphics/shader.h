#pragma once

#include "GL/glew.h"

#include "../math/math.h"

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

			void setUniform1f(const char *name, float value);
			void setUniform1i(const char *name, int value);
			void setUniform2f(const char *name, const math::vec2 &vec);
			void setUniform3f(const char *name, const math::vec3 &vec);
			void setUniform4f(const char *name, const math::vec4 &vec);
			void setUniformMat4(const char *name, const math::mat4 &mat);

		private:
			unsigned int init();
			int getUniformLocation(const char *name);
		};

	}
}