#pragma once
#include "text_renderer.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		TextRenderer::TextRenderer(GameObject& a_GameObj, std::string a_strText)
			: IComponent(s_COMPONENT_TYPE, a_GameObj)
		{
		
		}

		TextRenderer::~TextRenderer()
		{
		
		}

		void TextRenderer::addComponent(GameObject& a_GameObj, std::string a_strText)
		{
		
		}

		void TextRenderer::setText(std::string a_strText)
		{
		
		}

		void TextRenderer::setFont(std::string a_strFont)
		{
		
		}
	}
}