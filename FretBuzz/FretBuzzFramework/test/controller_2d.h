#pragma once

#include "system/scene_manager.h"
#include "system/core/input.h"
#include "components/gameobject_components/behaviour.h"

namespace ns_fretBuzz
{
	class controller_2d : public ns_system::Behaviour
	{

	public:
		controller_2d(ns_system::GameObject& a_GameObject)
			: ns_system::Behaviour(a_GameObject)
		{
		}

	protected:

		virtual void update(float a_fDeltaTime) override
		{
			if (ns_system::Input::IsKeyPutDown(GLFW_KEY_O))
			{
				ns_system::SceneManager::s_loadScene("3d_Test");
			}

			Behaviour::update(a_fDeltaTime);
		}
	};
}