#pragma once
#include "text_renderer.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		TextRenderer::TextRenderer(GameObject& a_GameObj, std::string a_strText)
			: IComponent(COMPONENT_TYPE::TEXT_RENDERER, a_GameObj)
		{
		
		}

		TextRenderer::~TextRenderer()
		{
		
		}

		TextRenderer* TextRenderer::addComponent(GameObject& a_GameObj, std::string a_strText)
		{
			return IComponent::isComponentOfTypeExistInGameObj(COMPONENT_TYPE::TEXT_RENDERER, &a_GameObj) ?
				nullptr : new TextRenderer(a_GameObj, a_strText);
		}

		void TextRenderer::setText(std::string a_strText)
		{
		
		}

		void TextRenderer::setFont(std::string a_strFont)
		{
		
		}
	}
}