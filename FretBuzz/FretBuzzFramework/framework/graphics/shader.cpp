#include <fretbuzz_pch.h>

#include "material.h"
#include "components/gameobject_components/camera.h"
#include "shader.h"
#include "utils/file_utils.h"

#include "shader_manager.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Shader::Shader(const std::string l_strShaderName, SHADER_TYPE a_ShaderType)
			: 
			m_strVertexShaderPath{ SHADER_PATH + l_strShaderName + VERT_SHADER_EXTENSION},
			m_strFragmentShaderPath{ SHADER_PATH + l_strShaderName + FRAG_SHADER_EXTENSION},
			m_ShaderType(a_ShaderType)
		{
			if (!initialize())
			{
				ENGINE_WARN("Shader::Shader:: Failed to intialize shader.");
			}
			else
			{
				ShaderManager::get()->registerShader(m_ShaderType, this);
			}
		}

		bool Shader::initialize()
		{
			std::string l_strVertexShaderSource = ns_utils::FileUtils::readFile(m_strVertexShaderPath);
			std::string l_strFragmentShaderSource = ns_utils::FileUtils::readFile(m_strFragmentShaderPath);

			const char* l_pVertexShaderFile = l_strVertexShaderSource.c_str();
			const char* l_pFragmentShaderFile = l_strFragmentShaderSource.c_str();

			m_ShaderID = glCreateProgram();
			GLuint l_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			GLuint l_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(l_VertexShaderID, 1, &l_pVertexShaderFile, NULL);
			glCompileShader(l_VertexShaderID);

			GLint l_result;
			glGetShaderiv(l_VertexShaderID, GL_COMPILE_STATUS, &l_result);
			if (l_result == GL_FALSE)
			{
				GLint l_ErrorLogLegth;
				glGetShaderiv(l_VertexShaderID, GL_INFO_LOG_LENGTH, &l_ErrorLogLegth);
				std::vector<char> l_vectorErrorLength(l_ErrorLogLegth);
				glGetShaderInfoLog(l_VertexShaderID, l_ErrorLogLegth, &l_ErrorLogLegth, &l_vectorErrorLength[0]);
				ENGINE_ERROR("Shader::initialize:: Error compiling vertex shader at path ::'{0}'::\n {1}", m_strVertexShaderPath , &l_vectorErrorLength[0]);
				glDeleteShader(l_VertexShaderID);
				return false;
			}

			glShaderSource(l_FragmentShaderID, 1, &l_pFragmentShaderFile, NULL);
			glCompileShader(l_FragmentShaderID);

			glGetShaderiv(l_FragmentShaderID, GL_COMPILE_STATUS, &l_result);
			if (l_result == GL_FALSE)
			{
				GLint l_ErrorLogLegth;
				glGetShaderiv(l_FragmentShaderID, GL_INFO_LOG_LENGTH, &l_ErrorLogLegth);
				std::vector<char> l_vectorErrorLength(l_ErrorLogLegth);
				glGetShaderInfoLog(l_FragmentShaderID, l_ErrorLogLegth, &l_ErrorLogLegth, &l_vectorErrorLength[0]);
				ENGINE_ERROR("Shader::initialize:: Error compiling fragment shader at path ::'{0}'::\n {1}", m_strFragmentShaderPath, &l_vectorErrorLength[0]);
				glDeleteShader(l_FragmentShaderID);
				glDeleteShader(l_VertexShaderID);
				return false;
			}

			glAttachShader(m_ShaderID, l_VertexShaderID);
			glAttachShader(m_ShaderID, l_FragmentShaderID);

			glLinkProgram(m_ShaderID);

			glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &l_result);
			if (l_result == GL_FALSE)
			{
				GLint l_ErrorLogLegth;
				glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &l_ErrorLogLegth);
				std::vector<char> l_vectorErrorLength(l_ErrorLogLegth);
				glGetProgramInfoLog(m_ShaderID, l_ErrorLogLegth, &l_ErrorLogLegth, &l_vectorErrorLength[0]);
				ENGINE_ERROR("Shader::initialize:: Failed to link program\n {0}",&l_vectorErrorLength[0]);
				glDeleteShader(l_FragmentShaderID);
				glDeleteShader(l_VertexShaderID);
				return false;
			}

			glValidateProgram(m_ShaderID);

			glDeleteShader(l_VertexShaderID);
			glDeleteShader(l_FragmentShaderID);

			return true;
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

		void Shader::setUniform1f(const char* a_pUniformName, GLfloat a_Float) const
		{
			glUniform1f(glGetUniformLocation(m_ShaderID, a_pUniformName), a_Float);
		}

		void Shader::setUniform1fv(const char* a_pUniformName, unsigned int a_iArrayCount, const GLfloat* a_arrValue) const
		{
			glUniform1fv(glGetUniformLocation(m_ShaderID, a_pUniformName), a_iArrayCount, a_arrValue);
		}

		void Shader::setUniform1d(const char* a_pUniformName, int a_iValue) const
		{
			glUniform1d(glGetUniformLocation(m_ShaderID, a_pUniformName), a_iValue);
		}

		void Shader::setUniform1dv(const char* a_pUniformName, unsigned int a_iArrayCount, const GLdouble* a_arrValue) const
		{
			glUniform1dv(glGetUniformLocation(m_ShaderID, a_pUniformName), a_iArrayCount, a_arrValue);
		}

		void Shader::setUniform1i(const char* a_pUniformName, GLint a_Value) const
		{
			glUniform1i(glGetUniformLocation(m_ShaderID, a_pUniformName), a_Value);
		}

		void Shader::setUniform1iv(const char* a_pUniformName, int a_iArrayCount, const GLint* a_arrValue) const
		{
			glUniform1iv(glGetUniformLocation(m_ShaderID, a_pUniformName), a_iArrayCount, a_arrValue);
		}

		void Shader::setUniform1ui(const char* a_pUniformName, GLuint a_Value) const
		{
			glUniform1ui(glGetUniformLocation(m_ShaderID, a_pUniformName), a_Value);
		}

		void Shader::setUniform1uiv(const char* a_pUniformName, unsigned int a_iArrayCount, GLuint* a_arrValue) const
		{
			glUniform1uiv(glGetUniformLocation(m_ShaderID, a_pUniformName), a_iArrayCount, a_arrValue);
		}

		void Shader::setUniform2f(const char* a_pUniformName, GLfloat a_value1, GLfloat a_value2) const
		{
			glUniform2f(glGetUniformLocation(m_ShaderID, a_pUniformName), a_value1, a_value2);
		}

		void Shader::setUniform2f(const char* a_pUniformName, const glm::vec2& a_vec2) const
		{
			setUniform2f(a_pUniformName, a_vec2.x, a_vec2.y);
		}

		void Shader::setUniform3f(const char* a_pUniformName, GLfloat a_value1, GLfloat a_value2, GLfloat a_value3) const
		{
			glUniform3f(glGetUniformLocation(m_ShaderID, a_pUniformName), a_value1, a_value2, a_value3);
		}

		void Shader::setUniform3f(const char* a_pUniformName, const glm::vec3& a_vec3) const
		{
			setUniform3f(a_pUniformName, a_vec3.x, a_vec3.y, a_vec3.z);
		}

		void Shader::setUniform4f(const char* a_pUniformName, GLfloat a_value1, GLfloat a_value2, GLfloat a_value3, GLfloat a_value4) const
		{
			glUniform4f(glGetUniformLocation(m_ShaderID, a_pUniformName), a_value1, a_value2, a_value3, a_value4);
		}

		void Shader::setUniform4f(const char* a_pUniformName, const glm::vec4& a_vec4) const
		{
			setUniform4f(a_pUniformName, a_vec4.x, a_vec4.y, a_vec4.z, a_vec4.w);
		}

		void Shader::setUniforMat4fv(const char* a_pUniformName, const glm::mat4& a_mat4) const
		{
			glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, a_pUniformName), 1, GL_FALSE, glm::value_ptr(a_mat4));
		}

		void Shader::setUniforMat3fv(const char* a_pUniformName, const glm::mat3& a_mat3) const
		{
			glUniformMatrix3fv(glGetUniformLocation(m_ShaderID, a_pUniformName), 1, GL_FALSE, glm::value_ptr(a_mat3));
		}

		GLint Shader::GetUniformLocation(GLuint a_ProgramID, const char* a_pUniformName) const
		{
			return glGetUniformLocation(a_ProgramID, a_pUniformName);
		}

		void Shader::bind(const Material& a_Material, const Camera& a_Camera) const
		{
			bind();
		}
	}
}