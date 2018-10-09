#include "material.h"
#include "../graphics/light_manager.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Material::Material()
		{
		
		}

		Material::~Material()
		{

		}

		Shader* Material::getShader()
		{
			return m_pShader;
		}

		void Material::setShader(Shader& a_Shader)
		{
			m_pShader = &a_Shader;
		}

		void Material::updateUniform()
		{
			m_pShader->setUniform1f(MaterialData::UNIF_MAT_SHININESS, 32.0f);

			glActiveTexture(GL_TEXTURE0);
			m_MaterialData.m_pTexDiffuse->bind();
			m_pShader->setUniform1i(MaterialData::UNIF_MAT_TEX_DIFFUSE, 0);

			glActiveTexture(GL_TEXTURE1);
			m_MaterialData.m_pTexSpecular->bind();
			m_pShader->setUniform1i(MaterialData::UNIF_MAT_TEX_SPECULAR, 1);

			LightManager::s_setAllLightUniforms(*m_pShader);
		}
	}
}