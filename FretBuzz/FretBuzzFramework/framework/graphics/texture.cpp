#pragma once
#include "texture.h"
#include "../utils/file_utils.h"
#include <string>
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Texture::Texture(std::string a_strTexturePath)
			: ns_system::IManagedResource()
		{
			if (!ns_utils::FileUtils::readImage(a_strTexturePath, m_pImageData, m_iWidth, m_iHeight))
			{
				std::cout << "Texture::Texture:: Failed to load image at path :: '" << a_strTexturePath << "' into texture.\n";
				m_pImageData = nullptr;
				return;
			}
			
			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_iWidth, m_iHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, m_pImageData);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Texture::Texture(Texture& a_Texture)
			: m_TextureID{a_Texture.m_TextureID},
			m_pImageData{ a_Texture.m_pImageData },
			m_iWidth{ a_Texture.m_iWidth},
			m_iHeight{ a_Texture.m_iHeight},
			ns_system::IManagedResource()
		{
			a_Texture.m_pImageData = nullptr;
		}

		Texture::~Texture()
		{
			
		}

		void Texture::destroyResource()
		{
			std::cout << "Unloading texture resource\n";
			if (m_pImageData != nullptr)
			{
				delete[] m_pImageData;
				m_pImageData = nullptr;
			}
		}

		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE, m_TextureID);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE, 0);
		}
	}
}