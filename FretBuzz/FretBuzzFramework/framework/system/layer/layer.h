#pragma once

namespace ns_fretBuzz
{
	class Layer
	{
		friend class LayerManager;

	public:
		//max layers count
		static constexpr unsigned int MAX_CAPACITY_LAYERS = 16;

		Layer();
		Layer(const std::string& a_strName);

	private:
		Layer(const std::string& a_strName, int a_uiID);

		std::string m_strName;
		int m_iID = 0;

	public:

		void changeLayer(const std::string& a_strName);
		void operator=(Layer a_Layer);

		const std::string& getName() const;
		int getID() const;
	};
}