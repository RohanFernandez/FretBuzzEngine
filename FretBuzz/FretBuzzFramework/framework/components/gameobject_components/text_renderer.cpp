#include <fretbuzz_pch.h>
#include "text_renderer.h"
#include <resource_manager.h>

namespace FRETBUZZ
{
	TextRenderer::TextRenderer(GameObject* a_GameObj, std::string a_strText, std::string a_strFontName)
		: IComponent(COMPONENT_TYPE::TEXT_RENDERER, a_GameObj)
	{
		setText(a_strText);
		setFont(a_strFontName);
	}

	TextRenderer::~TextRenderer()
	{
		
	}

	void TextRenderer::setText(std::string a_strText)
	{
		m_strText = a_strText;
	}

	void TextRenderer::setFont(std::string a_strFontName)
	{
		m_pFont = ResourceManager::getResource<Font>(a_strFontName);

		if (m_pFont == nullptr)
		{
			m_pFont = ResourceManager::getResource<Font>("");
		}
	}

	void TextRenderer::render(const glm::mat4& a_mat4Transformation, const Camera& a_Camera)
	{
		FT_Face l_FTFace = m_pFont->getFTFace();
			
	}
}