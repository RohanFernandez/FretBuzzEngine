#pragma once
#include "system/component.h"
#include <string>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class TextRenderer : public IComponent
		{
		private:
			TextRenderer(GameObject& a_GameObj, std::string a_strText);

			std::string m_strText;

		protected:
			virtual ~TextRenderer();

		public:
			static TextRenderer* addComponent(GameObject& a_GameObj, std::string a_strText);

			void setText(std::string a_strText);
			void setFont(std::string a_strFont);
		};
	}
}