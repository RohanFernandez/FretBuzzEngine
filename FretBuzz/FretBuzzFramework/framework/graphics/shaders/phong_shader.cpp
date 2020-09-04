#include <fretbuzz_pch.h>
#include "../material.h"
#include "components/gameobject_components/camera.h"
#include "../shader.h"
#include "phong_shader.h"
#include "../light_manager.h"
#include "system/game_object.h"

namespace FRETBUZZ
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
				ENGINE_WARN("PhongShader::initialize:: PhongShader previously initialized");
				return nullptr;
			}

			s_pInstance = new PhongShader(a_strShaderPath);
			return s_pInstance;
		}

		void PhongShader::bind(const Material& a_Material, const Camera& a_Camera) const
		{
			Shader::bind();

			setUniform3f(Material::MaterialData::UNIF_CAM_POSITION, a_Camera.m_GameObject.m_Transform.getWorldPosition());
			setUniform1f(Material::MaterialData::UNIF_MAT_SHININESS, a_Material.m_MaterialData.m_fShininess);

			setUniform4f(Material::MaterialData::UNIF_MAT_V4_ALBEDO, a_Material.m_MaterialData.m_v4Albedo);
			setUniform1iv(Material::MaterialData::UNIFORM_TEXTURE_SAMPLER, Material::MaterialData::TOTAL_TEXTURE_SLOTS, Material::MaterialData::s_arrTextureIDArray);

			if (a_Material.m_MaterialData.m_pTexDiffuse != nullptr)
			{
				glActiveTexture(GL_TEXTURE0);
				a_Material.m_MaterialData.m_pTexDiffuse->bind();
				setUniform1f(Material::MaterialData::UNIF_MAT_TEX_DIFFUSE, 1.0f);
			}
			else
			{
				setUniform1f(Material::MaterialData::UNIF_MAT_TEX_DIFFUSE, 0.0f);
			}

			if (a_Material.m_MaterialData.m_pTexSpecular != nullptr)
			{
				glActiveTexture(GL_TEXTURE1);
				a_Material.m_MaterialData.m_pTexSpecular->bind();
				setUniform1f(Material::MaterialData::UNIF_MAT_TEX_SPECULAR, 2.0f);
			}
			else
			{
				setUniform1f(Material::MaterialData::UNIF_MAT_TEX_SPECULAR, 0.0f);
			}

			LightManager::s_setAllLightUniforms(*this);
		}

		void PhongShader::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
}