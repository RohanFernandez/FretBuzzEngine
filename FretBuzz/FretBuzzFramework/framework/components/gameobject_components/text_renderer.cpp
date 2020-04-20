#include <fretbuzz_pch.h>
#include "text_renderer.h"
#include "system/core/resource_manager.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		TextRenderer::TextRenderer(ns_system::GameObject& a_GameObj, std::string a_strText, std::string a_strFontName)
			: ns_system::IComponent(ns_system::COMPONENT_TYPE::TEXT_RENDERER, a_GameObj)
		{
			setText(a_strText);
			setFont(a_strFontName);
		}

		TextRenderer::~TextRenderer()
		{
		
		}
		
		TextRenderer* TextRenderer::addToGameObject(ns_system::GameObject& a_GameObj, std::string a_strText, std::string a_strFontName)
		{
			return ns_system::IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::TEXT_RENDERER, &a_GameObj) ?
				nullptr : new TextRenderer(a_GameObj, a_strText, a_strFontName);
		}

		void TextRenderer::setText(std::string a_strText)
		{
			m_strText = a_strText;
		}

		void TextRenderer::setFont(std::string a_strFontName)
		{
			m_pFont = ns_system::ResourceManager::getResource<ns_graphics::Font>(a_strFontName);

			if (m_pFont == nullptr)
			{
				m_pFont = ns_system::ResourceManager::getResource<ns_graphics::Font>("");
			}
		}

		void TextRenderer::render(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera)
		{
			FT_Face l_FTFace = m_pFont->getFTFace();
			
		}
	}
}