#pragma once
#include "../framework/system/scene_manager.h"

#include "../framework/components/gameobject_components/camera.h"
#include "../test/PlayerController.h"
#include "../test/test_cube.h"

namespace ns_fretBuzz
{
	class threed_test_scene:
		public ns_system::IScene
	{
	private:
		ns_system::GameObject* m_pThreeDManager = nullptr;
		test_cube* m_pCube = nullptr;
		light_cube* m_pLightCube = nullptr;

	public:
		threed_test_scene(std::string a_strSceneName) 
			: IScene(a_strSceneName) 
		{
			ns_system::GameObject* m_pManager = ns_system::GameObject::instantiate(m_refRootGameObject, "3D_Manager", { 0.0f, 0.0f, 5.0f },
				{ 0.0f, M_PI, 0.0f }, { 1.0f, 1.0f, 1.0f });

			ns_system::PerspectiveViewport l_PerspectiveViewport(60.0f, 0.01, 1000.0f);
			ns_system::Camera::addToGameObject(*m_pManager, ns_system::Viewport::PROJECTION_TYPE::PERSPECTIVE, &l_PerspectiveViewport);
			ns_system::Behaviour::addToGameObject<PlayerController>(*m_pManager);

			m_pCube = new test_cube(m_refRootGameObject, "Cube");
			m_pLightCube = new light_cube(m_refRootGameObject, "Light");
			m_pCube->setLight(m_pLightCube);
			m_pCube->setCamGameObject(m_pManager);
		}

		virtual void OnStateEnter() override {};

		virtual void OnStateExit() override {};
	};
}