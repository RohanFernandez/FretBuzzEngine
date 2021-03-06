#include <fretbuzz_pch.h>
#include "texture.h"
#include "utils/file_utils.h"

namespace FRETBUZZ
{
	Texture::Texture(std::string a_strTexturePath)
		: IManagedResource()
	{
		if (!ns_utils::FileUtils::readImage(a_strTexturePath, m_pImageData, m_iWidth, m_iHeight, m_iChannels))
		{
			ENGINE_ERROR("Texture::Texture:: Failed to load image at path :: '{0}' into texture.", a_strTexturePath);
			m_pImageData = nullptr;
			m_bIsErrorWhileLoading = true;
			return;
		}

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLenum l_ColorFormat;
		GLenum l_ColorTarget;
		switch (m_iChannels)
		{
		case 3:
			l_ColorFormat = GL_BGR;
			l_ColorTarget = GL_RGB;
			break;
		case 4:
			l_ColorFormat = GL_BGRA;
			l_ColorTarget = GL_RGBA;
			break;
		default:
			ENGINE_ERROR("Texture::Texture:: Failed to detect texture channels ::{0} in texture {1}'", m_iChannels, a_strTexturePath);
			return;;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, l_ColorTarget, m_iWidth, m_iHeight, 0, l_ColorFormat, GL_UNSIGNED_BYTE, m_pImageData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::Texture(Texture& a_Texture)
		: m_TextureID{ a_Texture.m_TextureID },
		m_pImageData{ a_Texture.m_pImageData },
		m_iWidth{ a_Texture.m_iWidth },
		m_iHeight{ a_Texture.m_iHeight },
		IManagedResource(a_Texture.m_bIsErrorWhileLoading)
	{
	}

	Texture::Texture(Texture&& a_Texture)
		: m_TextureID{ a_Texture.m_TextureID },
		m_pImageData{ a_Texture.m_pImageData },
		m_iWidth{ a_Texture.m_iWidth },
		m_iHeight{ a_Texture.m_iHeight },
		IManagedResource(a_Texture.m_bIsErrorWhileLoading)
	{
		a_Texture.m_pImageData = nullptr;
	}

	Texture::Texture(unsigned int a_iTexWidth, unsigned int a_iTexHeight, GLenum a_ColorFormat)
		: m_iWidth{ a_iTexWidth },
		m_iHeight{ a_iTexHeight }

	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, a_ColorFormat, m_iWidth, m_iHeight, 0, a_ColorFormat, GL_UNSIGNED_BYTE, NULL);
	}

	Texture::~Texture()
	{
			
	}

	void Texture::operator=(Texture& a_Texture)
	{
		m_TextureID = a_Texture.m_TextureID;
		m_pImageData = a_Texture.m_pImageData;
		m_iWidth = a_Texture.m_iWidth;
		m_iHeight = a_Texture.m_iHeight;
		m_bIsErrorWhileLoading = a_Texture.m_bIsErrorWhileLoading;
	}

	void Texture::destroyResource()
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

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}