#pragma once
#include "sprite.h"
#include <cstddef>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		SpriteSheet::SpriteSheet(Texture* a_pTexture, Shader* a_pShader, std::vector<Sprite> a_vectSpriteData, float a_fTimePerSprite)
			: m_vectSpriteData{a_vectSpriteData},
			m_pTexture{a_pTexture },
			m_pShader{ a_pShader },
			m_fTimePerSprite{a_fTimePerSprite},
			 ns_system::IManagedResource()
		{
		}

		SpriteSheet::SpriteSheet(SpriteSheet& a_Sprite)
			: m_vectSpriteData{ a_Sprite.m_vectSpriteData },
			m_pTexture{ a_Sprite.m_pTexture },
			m_pShader{ a_Sprite.m_pShader},
			m_fTimePerSprite{ a_Sprite.m_fTimePerSprite },
			ns_system::IManagedResource()
		{
		
		}

		SpriteSheet::SpriteSheet(SpriteSheet&& a_Sprite)
			: m_vectSpriteData{ a_Sprite.m_vectSpriteData },
			m_pTexture{ a_Sprite.m_pTexture },
			m_pShader{ a_Sprite.m_pShader },
			m_fTimePerSprite{ a_Sprite.m_fTimePerSprite },
			 ns_system::IManagedResource()
		{
		
		}

		void SpriteSheet::operator=(SpriteSheet& a_Sprite)
		{
			m_pTexture = a_Sprite.m_pTexture;
			m_vectSpriteData = a_Sprite.m_vectSpriteData;
			m_pShader = a_Sprite.m_pShader;
			m_fTimePerSprite = a_Sprite.m_fTimePerSprite;
		}

		void SpriteSheet::operator=(SpriteSheet&& a_Sprite)
		{
			m_pTexture = a_Sprite.m_pTexture;
			m_vectSpriteData = a_Sprite.m_vectSpriteData;
			m_pShader = a_Sprite.m_pShader;
			m_fTimePerSprite = a_Sprite.m_fTimePerSprite;
		}

		SpriteSheet::~SpriteSheet()
		{
		
		}

		void SpriteSheet::destroyResource()
		{
			m_pTexture = nullptr;
			m_pShader = nullptr;
		}

		std::vector<Sprite>* SpriteSheet::getSpriteSheet()
		{
			return &m_vectSpriteData;
		}

		Sprite* SpriteSheet::getSprite(int l_iSpriteIndex)
		{
			return &m_vectSpriteData[l_iSpriteIndex];
		}
	}
}