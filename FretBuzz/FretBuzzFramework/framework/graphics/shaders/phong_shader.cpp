#pragma once
#include "../material.h"
#include "../../components/gameobject_components/camera.h"
#include "../shader.h"
#include "phong_shader.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		PhongShader* PhongShader::s_pInstance = nullptr;

		PhongShader::PhongShader(std::string a_strShaderPath)
			: Shader(a_strShaderPath, SHADER_TYPE::PHONG)
		{
		
		}

		PhongShader::~PhongShader()
		{

		}

		PhongShader* PhongShader::initialize(std::string a_strShaderPath)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "PhongShader::initialize:: PhongShader previously initialized\n";
				return nullptr;
			}

			s_pInstance = new PhongShader(a_strShaderPath);
			return s_pInstance;
		}

		void PhongShader::bind(const Material& a_Material, const Camera& a_Camera)
		{
			Shader::bind();
		}

		void PhongShader::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}
}