#pragma once
#include "system/core/managed_resource.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class  Font : public ns_system::IManagedResource
		{
			friend class FontManager;
		private:
			FT_Face m_FontFace = nullptr;
			std::string m_strName;

		public:
			Font(std::string a_strName);
			virtual ~Font();

			std::string getName();
			FT_Face getFTFace();

		protected:
			virtual void destroyResource();
		};
	}
}