#include <fretbuzz_pch.h>
#include "font_manager.h"
#include <ft2build.h>
#include "font.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Font::Font(std::string a_strName)
			: m_strName{ a_strName }
		{
		}

		Font::~Font()
		{
			
		}

		void Font::destroyResource()
		{
			
		}

		std::string Font::getName()
		{
			return m_strName;
		}

		FT_Face Font::getFTFace()
		{
			return m_FontFace;
		}
	}
}