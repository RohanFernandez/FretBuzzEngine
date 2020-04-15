#pragma once
#include "system/core/managed_resource.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class FRETBUZZ_API Font : public ns_system::IManagedResource
		{
			friend class FontManager;
		private:
			FT_Face m_FontFace = nullptr;
			std::string m_strName;

		public:
			Font(std::string a_strName);
			virtual ~Font();

			std::string getName();

		protected:
			virtual void destroyResource();
		};
	}
}