#pragma once
#include "../material.h"
#include "../../components/gameobject_components/camera.h"
#include "../shader.h"
#include "default_3d_shader.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		Default3DShader* Default3DShader::s_pInstance = nullptr;

		Default3DShader::Default3DShader(std::string a_strShaderPath)
			: Shader(a_strShaderPath, SHADER_TYPE::DEFAULT_3D)
		{

		}

		Default3DShader::~Default3DShader()
		{

		}

		Default3DShader* Default3DShader::initialize(std::string a_strShaderPath)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "PhongShader::initialize:: PhongShader previously initialized\n";
				return nullptr;
			}

			s_pInstance = new Default3DShader(a_strShaderPath);
			return s_pInstance;
		}

		void Default3DShader::bind(const Material& a_Material, const Camera& a_Camera)
		{
			Shader::bind();
		}

		void Default3DShader::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}
}