#pragma once
#include "texture.h"
#include <glew.h>
#include <string>
#include "../utils/file_utils.h"
#include "../system/core/managed_resource.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Texture : public ns_system::IManagedResource
		{
		protected:
			GLuint m_TextureID;
			BYTE* m_pImageData = nullptr;
			unsigned int m_iWidth = 0;
			unsigned int m_iHeight = 0;
			int m_iChannels = 0;

			virtual void destroyResource() override;

		public:
			Texture() = delete;
			Texture(std::string a_strTexturePath);

			//Copy constructor
			Texture(Texture& a_Texture);
			Texture(Texture&& a_Texture);
			~Texture();


			void operator=(Texture& a_Texture);


			void bind() const;
			void unbind() const;

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