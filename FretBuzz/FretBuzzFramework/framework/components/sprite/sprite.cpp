#pragma once
#include "sprite.h"
#include <cstddef>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		SpriteSheet::SpriteSheet(Texture* a_pTexture, Shader* a_pShader, std::vector<Sprite> a_vectSpriteData)
			: m_vectSpriteData{a_vectSpriteData},
			m_pTexture{a_pTexture },
			m_pShader{ a_pShader },
			 ns_system::IManagedResource()
		{
		}

		SpriteSheet::SpriteSheet(SpriteSheet& a_Sprite)
			: m_vectSpriteData{ a_Sprite.m_vectSpriteData },
			m_pTexture{ a_Sprite.m_pTexture },
			m_pShader{ a_Sprite.m_pShader},
			m_IBO{ a_Sprite.m_IBO },
			m_VBO{ a_Sprite.m_VBO },
			m_VAO{ a_Sprite.m_VAO },
			ns_system::IManagedResource()
		{
		
		}

		SpriteSheet::SpriteSheet(SpriteSheet&& a_Sprite)
			: m_vectSpriteData{ a_Sprite.m_vectSpriteData },
			m_pTexture{ a_Sprite.m_pTexture },
			m_pShader{ a_Sprite.m_pShader },
			m_IBO{ a_Sprite .m_IBO}, 
			m_VBO{ a_Sprite.m_VBO },
			m_VAO{ a_Sprite.m_VAO },
			 ns_system::IManagedResource()
		{
		
		}

		void SpriteSheet::operator=(SpriteSheet& a_Sprite)
		{
			m_pTexture = a_Sprite.m_pTexture;
			m_vectSpriteData = a_Sprite.m_vectSpriteData;
			m_pShader = a_Sprite.m_pShader;
		}

		void SpriteSheet::operator=(SpriteSheet&& a_Sprite)
		{
			m_pTexture = a_Sprite.m_pTexture;
			m_vectSpriteData = a_Sprite.m_vectSpriteData;
			m_pShader = a_Sprite.m_pShader;
		}

		SpriteSheet::~SpriteSheet()
		{
		
		}

		void SpriteSheet::destroyResource()
		{
			m_pTexture = nullptr;
			m_pShader = nullptr;
		}

		std::vector<Sprite>* SpriteSheet::getSprites()
		{
			return &m_vectSpriteData;
		}

		Sprite* SpriteSheet::getSprite(int l_iSpriteIndex)
		{
			return &m_vectSpriteData[l_iSpriteIndex];
		}
	}
}