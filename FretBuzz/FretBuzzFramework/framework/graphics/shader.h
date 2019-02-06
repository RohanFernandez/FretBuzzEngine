#pragma once
#include <glew.h>
#include "system/core/managed_resource.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Camera;
		class Material;
		class FRETBUZZ_API Shader
		{
		public:
			friend class ShaderManager;

			enum SHADER_TYPE
			{
				DEFAULT_SPRITE,
				DEFAULT_LINE,
				DEFAULT_3D,
				PHONG,

				PP_DEFAULT
			};

		protected:
			GLuint m_ShaderID = 0;

			//creates the shader and retuns if successfully initialized without error.
			bool initialize();

			std::string m_strVertexShaderPath;
			std::string m_strFragmentShaderPath;

			SHADER_TYPE m_ShaderType;

			Shader() = delete;
			Shader(const std::string l_strShaderName, SHADER_TYPE a_ShaderType = SHADER_TYPE::DEFAULT_SPRITE);
			~Shader();

		public:
			static constexpr char VERT_SHADER_EXTENSION[] = ".vs";
			static constexpr char FRAG_SHADER_EXTENSION[] = ".fs";
			static constexpr char SHADER_PATH[] = "resources//shaders//";

			void bind()  const;
			void unbind() const;

			inline SHADER_TYPE getShaderType()
			{
				return m_ShaderType;
			}

			inline GLuint getShaderId() const
			{
				return m_ShaderID;
			}

			void setUniform1f(const char* a_pUniformName, GLfloat a_Value) const;
			void setUniform1fv(const char* a_pUniformName, unsigned int a_iArrayCount, const GLfloat* a_arrValue) const;

			void setUniform1d(const char* a_pUniformName, int a_iValue) const;
			void setUniform1dv(const char* a_pUniformName, unsigned int a_iArrayCount, const GLdouble* a_arrValue) const;

			void setUniform1i(const char* a_pUniformName, GLint a_Value) const;
			void setUniform1iv(const char* a_pUniformName, int a_iArrayCount, const GLint* a_arrValue) const;

			void setUniform1ui(const char* a_pUniformName, GLuint a_Value) const;
			void setUniform1uiv(const char* a_pUniformName, unsigned int a_iArrayCount, GLuint* a_arrValue) const;

			void setUniform2f(const char* a_pUniformName, const glm::vec2& a_vec2) const;
			void setUniform2f(const char* a_pUniformName, GLfloat a_value1, GLfloat a_value2) const;

			void setUniform3f(const char* a_pUniformName, const glm::vec3& a_vec3) const;
			void setUniform3f(const char* a_pUniformName, GLfloat a_value1, GLfloat a_value2, GLfloat a_value3) const;

			void setUniform4f(const char* a_pUniformName, const glm::vec4& a_vec4) const;
			void setUniform4f(const char* a_pUniformName, GLfloat a_value1, GLfloat a_value2, GLfloat a_value3, GLfloat a_value4) const;

			void setUniforMat4fv(const char* a_pUniformName, const glm::mat4& a_mat4) const;
			void setUniforMat3fv(const char* a_pUniformName, const glm::mat3& a_mat3) const;

			GLint GetUniformLocation(GLuint a_ProgramID, const char* a_pUniformName) const;

			virtual void bind(const Material& a_Material, const Camera& a_Camera) const;
			virtual void destroy() = 0;
		};
	}
}