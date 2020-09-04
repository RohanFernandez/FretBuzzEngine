#include <fretbuzz_pch.h>
#include "../material.h"
#include "components/gameobject_components/camera.h"
#include "../shader.h"
#include "default_post_process.h"

namespace FRETBUZZ
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
			ENGINE_WARN("DefaultLineShader::initialize:: DefaultLineShader previously initialized");
			return nullptr;
		}

		s_pInstance = new DefaultPostProcess(a_strShaderPath);
		return s_pInstance;
	}

	void DefaultPostProcess::bind(const Material& a_Material, const Camera& a_Camera) const
	{
		Shader::bind();
		a_Material.m_pShader->setUniform1i(UNIF_SCREEN_TEXTURE, UNIF_SCREEN_TEXTURE_SAMPLE_ID);
		a_Material.m_pShader->setUniform1fv(UNIF_ARRAY_KERNEL, s_iKERNEL_SIZE, getKernel(a_Material));
	}

	void DefaultPostProcess::destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	const float* DefaultPostProcess::getKernel(Material a_Material)
	{
		switch (a_Material.m_MaterialData.m_PostProcessType)
		{
		case Material::POST_PROCESS_TYPE::EDGE_DETECT:
			return s_arrEdgeDetectKernel;

		case Material::POST_PROCESS_TYPE::BLUR:
			return s_arrBlurKernel;

		case Material::POST_PROCESS_TYPE::SHARPEN:
			return s_arrSharpenKernel;
		default:
			return nullptr;
		}
	}
}