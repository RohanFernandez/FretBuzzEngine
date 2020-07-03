#include <fretbuzz_pch.h>
#include "../material.h"
#include "components/gameobject_components/camera.h"
#include "../shader.h"
#include "default_3d_shader.h"

namespace ns_fretBuzz
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
			ENGINE_WARN("Default3DShader::initialize:: Default3DShader previously initialized");
			return nullptr;
		}

		s_pInstance = new Default3DShader(a_strShaderPath);
		return s_pInstance;
	}

	void Default3DShader::bind(const Material& a_Material, const Camera& a_Camera) const
	{
		Shader::bind();
		a_Material.m_pShader->setUniform4f(Material::MaterialData::UNIF_MAT_V4_ALBEDO, a_Material.m_MaterialData.m_v4Albedo);
	}

	void Default3DShader::destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}
}