#pragma once
#include "system/component.h"
#include "graphics/font_manager.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class FRETBUZZ_API TextRenderer : public ns_system::IComponent
		{
		private:

			ns_graphics::Font* m_pFont = nullptr;

			std::string m_strText;

		protected:
			virtual ~TextRenderer();

		public:
			TextRenderer(ns_system::GameObject* a_GameObj, std::string a_strText, std::string a_strFontName);

			void setText(std::string a_strText);
			void setFont(std::string a_strFontName);

			virtual void render(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera) override;
		};
	}
}