#pragma once
#include "../material.h"
#include "../../components/gameobject_components/camera.h"
#include "../shader.h"
#include "default_post_process.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		DefaultPostProcess* DefaultPostProcess::s_pInstance = nullptr;

		DefaultPostProcess::DefaultPostProcess(std::string a_strShaderPath)
			: Shader(a_strShaderPath, SHADER_TYPE::PP_DEFAULT)
		{

		}

		DefaultPostProcess::~DefaultPostProcess()
		{

		}

		DefaultPostProcess* DefaultPostProcess::initialize(std::string a_strShaderPath)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "DefaultLineShader::initialize:: DefaultLineShader previously initialized\n";
				return nullptr;
			}

			s_pInstance = new DefaultPostProcess(a_strShaderPath);
			return s_pInstance;
		}

		void DefaultPostProcess::bind(const Material& a_Material, const Camera& a_Camera) const
		{
			Shader::bind();
			a_Material.m_pShader->setUniform1i("screenTexture", 0);
		}

		void DefaultPostProcess::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}
}