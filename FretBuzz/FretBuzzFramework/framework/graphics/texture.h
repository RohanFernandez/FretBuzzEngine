#pragma once
#include "texture.h"
#include <glew.h>
#include <string>
#include "../utils/file_utils.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Texture
		{
		private:
			GLuint m_TextureID;
			BYTE* m_pImageData = nullptr;
			unsigned int m_iWidth = 0;
			unsigned int m_iHeight = 0;


		public:
			Texture(std::string a_strTexturePath);
			~Texture();

			void bind();
			void unbind();

			inline const unsigned int getWidth() const
			{
				return m_iWidth;
			}

			inline const unsigned int getHeight() const
			{
				return m_iHeight;
			}

			inline const unsigned int getID() const
			{
				return m_TextureID;
			}
		};
	}
}