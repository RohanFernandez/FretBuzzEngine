#pragma once
#include <fretbuzz.h>
#include "scene_manager.h"

namespace ns_fretBuzz
{
	class SystemLayerBase
	{
	private:
		std::string m_strName;

	public:
		SystemLayerBase()
			: m_strName{ "Layer" }
		{
		};

		SystemLayerBase(std::string a_strName = "Layer")
			: m_strName{ a_strName }
		{
		};
		virtual ~SystemLayerBase(){};

		inline const std::string& getName() { return m_strName;}
		virtual void update(const float& a_fDeltaTime, SceneManager& a_SceneManager) {};
		virtual void lateUpdate(const float& a_fDeltaTime, SceneManager& a_SceneManager) {};
		virtual void physicsUpdate(const float& a_fDeltaTime, SceneManager& a_SceneManager) {};
		virtual void render(SceneManager& a_SceneManager) {};
		virtual void onAttach() {};
		virtual void onDetached() {};
	};
}