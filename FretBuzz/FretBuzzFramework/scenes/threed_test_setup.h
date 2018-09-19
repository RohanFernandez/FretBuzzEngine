#pragma once
#include "../framework/system/scene_manager.h"

#include "../framework/components/gameobject_components/camera.h"
#include "../test/three_d_manager.h"
#include "../test/test_cube.h"

namespace ns_fretBuzz
{
	class threed_test_scene:
		public ns_system::IScene
	{
	private:
		ns_system::GameObject* m_pThreeDManager = nullptr;
		ns_system::GameObject* m_pCube = nullptr;

	public:
		threed_test_scene(std::string a_strSceneName) 
			: IScene(a_strSceneName) 
		{
			m_pThreeDManager = new three_d_manager(m_refRootGameObject, "3D_Manager");
			m_pCube = new test_cube(m_refRootGameObject, "Cube");
		}

		virtual void OnStateEnter() override {};

		virtual void OnStateExit() override {};
	};
}