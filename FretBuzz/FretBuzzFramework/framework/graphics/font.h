#pragma once
#include <managed_resource.h>

namespace FRETBUZZ
{
	class  Font : public IManagedResource
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