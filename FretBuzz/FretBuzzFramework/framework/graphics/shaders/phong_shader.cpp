#pragma once
#include "../material.h"
#include "../../components/gameobject_components/camera.h"
#include "../shader.h"
#include "phong_shader.h"
#include "../light_manager.h"
#include "../../system/game_object.h"
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

			setUniform3f(Material::MaterialData::UNIF_CAM_POSITION, a_Camera.m_GameObject.m_Transform.getWorldPosition());
			setUniform1f(Material::MaterialData::UNIF_MAT_SHININESS, a_Material.m_MaterialData.m_fShininess);

			setUniform4f(Material::MaterialData::UNIF_MAT_V4_ALBEDO, a_Material.m_MaterialData.m_v4Albedo);

			glActiveTexture(GL_TEXTURE0);
			a_Material.m_MaterialData.m_pTexDiffuse->bind();
			setUniform1i(Material::MaterialData::UNIF_MAT_TEX_DIFFUSE, 0);

			glActiveTexture(GL_TEXTURE1);
			a_Material.m_MaterialData.m_pTexSpecular->bind();
			setUniform1i(Material::MaterialData::UNIF_MAT_TEX_SPECULAR, 1);

			LightManager::s_setAllLightUniforms(*this);
		}

		void PhongShader::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}
}