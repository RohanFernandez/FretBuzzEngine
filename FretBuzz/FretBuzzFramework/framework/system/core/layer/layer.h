#pragma once

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class FRETBUZZ_API Layer
		{
			friend class LayerManager;

		public:
			//max layers count
			static constexpr unsigned int MAX_CAPACITY_LAYERS = 16;

			Layer();

		private:
			Layer(std::string a_strName, int a_uiID);

			std::string m_strName;
			int m_iID = 0;

		public:

			void changeLayer(std::string a_strName);
			void operator=(Layer a_Layer);

			std::string getName() const;
			int getID() const;
		};
	}
}