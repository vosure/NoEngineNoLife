#include "shader.h"
#include <iostream>
#include "../utils/file_utils.h"

namespace core {
	namespace graphics {



		Shader::Shader(const char * vertexPath, const char * fragmenPath)
			: m_VertexPath(vertexPath), m_FragmentPath(fragmenPath)
		{
			m_ShaderID = init();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
		}

		void Shader::bind() const
		{
			glUseProgram(m_ShaderID);
		}

		void Shader::unbind() const
		{
			glUseProgram(0);
		}

		void Shader::setUniform1f(const char * name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform1i(const char * name, int value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform2f(const char * name, const math::vec2 & vec)
		{
			glUniform2f(getUniformLocation(name), vec.x, vec.y);
		}

		void Shader::setUniform3f(const char * name, const math::vec3 & vec)
		{
			glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
		}

		void Shader::setUniform4f(const char * name, const math::vec4 & vec)
		{
			glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
		}

		void Shader::setUniformMat4(const char * name, const math::mat4 & mat)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, mat.elements);
		}

		unsigned int Shader::init()
		{
			unsigned int program = glCreateProgram();

			unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
			unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string v = read_file(m_VertexPath);
			std::string f = read_file(m_FragmentPath);

			const char *vertexSource = v.c_str();
			const char *fragmentSource = f.c_str();


			glShaderSource(vertex, 1, &vertexSource, NULL);
			glShaderSource(fragment, 1, &fragmentSource, NULL);

			glCompileShader(vertex);
			glCompileShader(fragment);

			int status;
			char infoLog[512];
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				glGetShaderInfoLog(vertex, sizeof(infoLog), NULL, infoLog);
				std::cout << "ERROR::VERTEX SHADER COMPILE STATUS" << infoLog << std::endl;
			}

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
			if (!status)
			{
				glGetShaderInfoLog(fragment, sizeof(infoLog), NULL, infoLog);
				std::cout << "ERROR::FRAGMENT SHADER COMPILE STATUS" << infoLog << std::endl;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			glLinkProgram(program);

			glGetProgramiv(program, GL_LINK_STATUS, &status);
			if (!status)
			{
				glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
				std::cout << "ERROR::PROGRAM LINK STATUS" << infoLog << std::endl;
				return 0;
			}

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		int Shader::getUniformLocation(const char * name)
		{
			return glGetUniformLocation(m_ShaderID, name);
		}

	}
}