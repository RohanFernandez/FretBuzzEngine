#pragma once
#include "../system/component.h"
#include <string>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class TextRenderer : public IComponent
		{
		private:
			TextRenderer(GameObject& a_GameObj, std::string a_strText);
			virtual ~TextRenderer();

			std::string m_strText;

			static constexpr COMPONENT_TYPE s_COMPONENT_TYPE = COMPONENT_TYPE::TEXT_RENDERER;

		public:
			static void addComponent(GameObject& a_GameObj, std::string a_strText);

			void setText(std::string a_strText);
			void setFont(std::string a_strFont);
		};
	}
}