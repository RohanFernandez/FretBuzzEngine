#pragma once
#include "sprite.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Sprite::Sprite(Texture& a_Texture, std::vector<SpriteData> a_vectSpriteData)
			: m_vectSpriteData{a_vectSpriteData},
			  m_Texture{a_Texture},
			 ns_system::IManagedResource()
		{
		
		}

		Sprite::Sprite(Sprite& a_Sprite)
			: m_vectSpriteData{ a_Sprite.m_vectSpriteData },
			  m_Texture{ a_Sprite.m_Texture },
			  ns_system::IManagedResource()
		{
		
		}

		Sprite::Sprite(Sprite&& a_Sprite)
			: m_vectSpriteData{ a_Sprite.m_vectSpriteData },
			  m_Texture{ a_Sprite.m_Texture },
			  ns_system::IManagedResource()
		{
		
		}

		void Sprite::operator=(Sprite& a_Sprite)
		{
			m_Texture = a_Sprite.m_Texture;
			m_vectSpriteData = a_Sprite.m_vectSpriteData;
		}

		void Sprite::operator=(Sprite&& a_Sprite)
		{
			m_Texture = a_Sprite.m_Texture;
			m_vectSpriteData = a_Sprite.m_vectSpriteData;
		}

		Sprite::~Sprite()
		{
		
		}

		void Sprite::destroyResource()
		{
			
		}

		const std::vector<SpriteData> Sprite::getSpriteData() const
		{
			return m_vectSpriteData;
		}
	}
}