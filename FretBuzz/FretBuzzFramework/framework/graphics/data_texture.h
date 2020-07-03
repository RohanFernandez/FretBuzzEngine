#pragma once
#include "texture.h"

namespace ns_fretBuzz
{
	class  DataTexture : public Texture
	{
	private:
		GLenum m_ColorFormat;

	public:
		DataTexture(unsigned int a_uiWidth, unsigned int a_uiHeight, void* a_pData, GLenum a_ColorFormat);
		virtual ~DataTexture();

		void resetTextureDimension(unsigned int a_uiWidth, unsigned int a_uiHeight);
	};
}