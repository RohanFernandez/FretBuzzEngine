#pragma once
#include <glew.h>
#include <string>
#include "../utils/math.h"
#include "../system/managed_resource.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Shader : public ns_system::IManagedResource
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

			//Copy constructor
			Shader(Shader& a_Shader);
			Shader(Shader&& a_Shader);

			void operator=(Shader& a_Shader);
			void operator=(Shader&& a_Shader);

			~Shader();

			virtual void destroyResource() override;

			void bind()  const;
			void unbind() const;

			inline GLuint getShaderId() const
			{
				return m_ShaderID;
			}

			void setUniform1f(const char* a_pUniformName, GLfloat a_Value) const;
			void setUniform1fv(const char* a_pUniformName, unsigned int a_iArrayCount, const GLfloat* a_arrValue) const;

			void setUniform1d(const char* a_pUniformName, int a_iValue) const;
			void setUniform1dv(const char* a_pUniformName, unsigned int a_iArrayCount, const GLdouble* a_arrValue) const;

			void setUniform1i(const char* a_pUniformName, GLint a_Value) const;
			void setUniform1iv(const char* a_pUniformName, unsigned int a_iArrayCount, GLint* a_arrValue) const;

			void setUniform1ui(const char* a_pUniformName, GLuint a_Value) const;
			void setUniform1uiv(const char* a_pUniformName, unsigned int a_iArrayCount, GLuint* a_arrValue) const;

			void setUniform2f(const char* a_pUniformName, const glm::vec2& a_vec2) const;
			void setUniform2f(const char* a_pUniformName, GLfloat a_value1, GLfloat a_value2) const;

			void setUniform3f(const char* a_pUniformName, const glm::vec3& a_vec3) const;
			void setUniform3f(const char* a_pUniformName, GLfloat a_value1, GLfloat a_value2, GLfloat a_value3) const;

			void setUniform4f(const char* a_pUniformName, const glm::vec4& a_vec4) const;
			void setUniform4f(const char* a_pUniformName, GLfloat a_value1, GLfloat a_value2, GLfloat a_value3, GLfloat a_value4) const;

			void setUniforMat4fv(const char* a_pUniformName, const glm::mat4& a_mat4) const;

			GLint GetUniformLocation(GLuint a_ProgramID, const char* a_pUniformName) const;

		};
	}
}