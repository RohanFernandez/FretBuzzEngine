#pragma once
#include "sprite.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Sprite::Sprite(int a_iTextureID, Texture a_Texture, std::vector<SpriteData> a_vectSpriteData)
			: m_vectSpriteData{a_vectSpriteData},
			  m_Texture{a_Texture}
		{
		
		}

		Sprite::Sprite(Sprite& a_Sprite)
			: m_vectSpriteData{ a_Sprite.m_vectSpriteData },
			  m_Texture{ a_Sprite.m_Texture }
		{
		
		}

		Sprite::Sprite(Sprite&& a_Sprite)
			: m_vectSpriteData{ a_Sprite.m_vectSpriteData },
			  m_Texture{ a_Sprite.m_Texture }
		{
		
		}

		void Sprite::operator=(Sprite a_Sprite)
		{
			m_Texture = a_Sprite.m_Texture;
			m_vectSpriteData = a_Sprite.m_vectSpriteData;
		}

		Sprite::~Sprite()
		{
		
		}

		const std::vector<SpriteData> Sprite::getSpriteData() const
		{
			return m_vectSpriteData;
		}
	}
}