#pragma once
#include <glew.h>
#include <string>
#include "../components/math.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Shader
		{
		private:
			GLuint m_ShaderID = 0;

			//creates the shader and retuns if successfully initialized without error.
			bool initialize();

			std::string m_strVertexShaderPath;
			std::string m_strFragmentShaderPath;

		public:
			Shader() = delete;
			Shader(const std::string l_strVertexShaderPath, const std::string l_strFragmentShaderPath);
			~Shader();

			void bind();
			void unbind();

			inline GLuint getShaderId() const
			{
				return m_ShaderID;
			}

			void setUniform1f(const char* a_pUniformName, GLfloat a_Value);
			void setUniform1fv(const char* a_pUniformName, unsigned int a_iArrayCount, const GLfloat* a_arrValue);

			void setUniform1d(const char* a_pUniformName, int a_iValue);
			void setUniform1dv(const char* a_pUniformName, unsigned int a_iArrayCount, const GLdouble* a_arrValue);

			void setUniform1i(const char* a_pUniformName, GLint a_Value);
			void setUniform1iv(const char* a_pUniformName, unsigned int a_iArrayCount, GLint* a_arrValue);

			void setUniform1ui(const char* a_pUniformName, GLuint a_Value);
			void setUniform1uiv(const char* a_pUniformName, unsigned int a_iArrayCount, GLuint* a_arrValue);

			void setUniform2f(const char* a_pUniformName, const glm::vec2& a_vec2);
			void setUniform2f(const char* a_pUniformName, GLfloat a_value1, GLfloat a_value2);

			void setUniform3f(const char* a_pUniformName, const glm::vec3& a_vec3);
			void setUniform3f(const char* a_pUniformName, GLfloat a_value1, GLfloat a_value2, GLfloat a_value3);

			void setUniform4f(const char* a_pUniformName, const glm::vec4& a_vec4);
			void setUniform4f(const char* a_pUniformName, GLfloat a_value1, GLfloat a_value2, GLfloat a_value3, GLfloat a_value4);

			void setUniforMat4fv(const char* a_pUniformName, const glm::mat4& a_mat4);

			GLint GetUniformLocation(GLuint a_ProgramID, const char* a_pUniformName);

		};
	}
}