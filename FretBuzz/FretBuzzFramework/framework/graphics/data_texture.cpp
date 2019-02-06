#include <fretbuzz_pch.h>
#include "data_texture.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		DataTexture::DataTexture(unsigned int a_uiWidth, unsigned int a_uiHeight, void* a_pData, GLenum a_ColorFormat)
			: Texture()
		{
			m_iWidth = a_uiWidth;
			m_iHeight = a_uiHeight;
			m_ColorFormat = a_ColorFormat;

			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);
			glTexImage2D(GL_TEXTURE_2D, 0, m_ColorFormat, m_iWidth, m_iHeight, 0, m_ColorFormat, GL_UNSIGNED_BYTE, a_pData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		DataTexture::~DataTexture()
		{
			if (m_pImageData != nullptr)
			{
				delete[] m_pImageData;
				m_pImageData = nullptr;
			}

			if (m_TextureID)
			{
				glDeleteTextures(1, &m_TextureID);
				m_TextureID = 0;
			}
		}

		void DataTexture::resetTextureDimension(unsigned int a_uiWidth, unsigned int a_uiHeight)
		{
			bind();
			m_iWidth = a_uiWidth;
			m_iHeight = a_uiHeight;
			glTexImage2D(GL_TEXTURE_2D, 0, m_ColorFormat, m_iWidth, m_iHeight, 0, m_ColorFormat, GL_UNSIGNED_BYTE, nullptr);
		}
	}
}