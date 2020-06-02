#pragma once
#include <fretbuzz.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class SystemLayerBase
		{
		private:
			std::string m_strName;

		protected:
			SystemLayerBase(std::string a_strName = "Layer")
				: m_strName{a_strName}
			{
			};

			virtual ~SystemLayerBase() = 0 {};

		public:
			inline const std::string& getName() { return m_strName;}

			virtual void update() {};
			virtual void render() {};
		};
	}
}