#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include "font.h"


namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class  FontManager
		{
		private:
			//singleton instance
			static FontManager* s_pInstance;

			FontManager();
			~FontManager();

			FT_Library  m_FontLibrary;

		public:
			static FontManager* initialize();
			static const FontManager* get();
			void destroy();

			static Font createFont(std::string a_strFontName, std::string a_strLocation);

			static const std::string DEFAULT_FONT_NAME;
		};
	}
}