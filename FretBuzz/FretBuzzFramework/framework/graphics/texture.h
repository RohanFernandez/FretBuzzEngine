#pragma once
#include "texture.h"
#include <GL/glew.h>
#include "utils/file_utils.h"
#include "system/core/managed_resource.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class  Texture : public ns_system::IManagedResource
		{
		protected:
			GLuint m_TextureID;
			BYTE* m_pImageData = nullptr;
			unsigned int m_iWidth = 0;
			unsigned int m_iHeight = 0;
			int m_iChannels = 0;

			virtual void destroyResource() override;

			Texture() {};
		public:
			Texture(std::string a_strTexturePath);

			//Setup texture that holds null data
			Texture(unsigned int a_iTexWidth, unsigned int a_iTexHeight, GLenum a_ColorFormat);

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