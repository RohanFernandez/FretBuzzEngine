#include <fretbuzz_pch.h>
#include "../material.h"
#include "components/gameobject_components/camera.h"
#include "../shader.h"
#include "default_line_shader.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		DefaultLineShader* DefaultLineShader::s_pInstance = nullptr;

		DefaultLineShader::DefaultLineShader(std::string a_strShaderPath)
			: Shader(a_strShaderPath, SHADER_TYPE::DEFAULT_LINE)
		{

		}

		DefaultLineShader::~DefaultLineShader()
		{

		}

		DefaultLineShader* DefaultLineShader::initialize(std::string a_strShaderPath)
		{
			if (s_pInstance != nullptr)
			{
				ENGINE_WARN("DefaultLineShader::initialize:: DefaultLineShader previously initialized");
				return nullptr;
			}

			s_pInstance = new DefaultLineShader(a_strShaderPath);
			return s_pInstance;
		}

		void DefaultLineShader::bind(const Material& a_Material, const Camera& a_Camera) const
		{
			Shader::bind();
		}

		void DefaultLineShader::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}
}