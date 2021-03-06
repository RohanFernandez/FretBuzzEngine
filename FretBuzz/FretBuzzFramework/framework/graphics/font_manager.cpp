#include <fretbuzz_pch.h>
#include "font_manager.h"

namespace FRETBUZZ
{
	//singleton
	FontManager* FontManager::s_pInstance = nullptr;

	const std::string FontManager::DEFAULT_FONT_NAME= "";

	FontManager::FontManager()
	{
		FT_Error l_error = FT_Init_FreeType(&m_FontLibrary);
		if (l_error)
		{
			ENGINE_ERROR("FontManager::FontManager:: Error occured on Font Manager initialization");
		}
	}

	FontManager::~FontManager()
	{
			
	}

	FontManager* FontManager::initialize()
	{
		if (s_pInstance != nullptr)
		{
			return nullptr;
		}
		s_pInstance = new FontManager();
		return s_pInstance;
	}

	const FontManager* FontManager::get()
	{
		return s_pInstance;
	}

	void FontManager::destroy()
	{
		if (s_pInstance == this)
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}

	Font FontManager::createFont(std::string a_strFontName, std::string a_strLocation)
	{
		Font l_Font(a_strFontName);
		FT_Error l_error = FT_New_Face(s_pInstance->m_FontLibrary, a_strLocation.c_str(), 0, &l_Font.m_FontFace);

		if (l_error == FT_Err_Unknown_File_Format)
		{
			ENGINE_WARN("FontManager::getFont:: File at location '{0}' is unsupported.", a_strLocation);
		}
		else if (l_error)
		{
			ENGINE_WARN("FontManager::getFont:: File at location {0} is broken with eror ",l_error);
		}
		return l_Font;
	}
}