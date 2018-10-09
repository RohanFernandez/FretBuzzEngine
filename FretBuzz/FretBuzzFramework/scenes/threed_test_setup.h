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
		test_cube* m_pCube1 = nullptr;
		test_cube* m_pCube2 = nullptr;
		test_cube* m_pCube3 = nullptr;

		light_cube* m_pLightCube1 = nullptr;
		light_cube* m_pLightCube2 = nullptr;

	public:
		threed_test_scene(std::string a_strSceneName) 
			: IScene(a_strSceneName) 
		{
			ns_system::GameObject* m_pManager = ns_system::GameObject::instantiate(m_refRootGameObject, "3D_Manager", { 0.0f, 0.0f, 5.0f },
				{ 0.0f, M_PI, 0.0f }, { 1.0f, 1.0f, 1.0f });

			ns_graphics::PerspectiveViewport l_PerspectiveViewport(60.0f, 0.01, 1000.0f);
			ns_graphics::Camera::addToGameObject(*m_pManager, ns_graphics::Viewport::PROJECTION_TYPE::PERSPECTIVE, &l_PerspectiveViewport);
			ns_system::Behaviour::addToGameObject<PlayerController>(*m_pManager);

			m_pCube1 = new test_cube(m_refRootGameObject, "Cube1", {-2.0f, 3.0f, -1.0f});
			m_pCube2 = new test_cube(m_refRootGameObject, "Cube2", { 1.0f, 4.0f, 3.0f });
			m_pCube3 = new test_cube(m_refRootGameObject, "Cube3", { 2.0f, 0.0f, 0.0f });

			m_pLightCube1 = new light_cube(*m_pManager, "Light1", {0.0f, 0.0f, 0.0f}, ns_graphics::Light::LIGHT_TYPE::SPOT, 1.0f);
			m_pLightCube2 = new light_cube(m_refRootGameObject, "Light2", { 1.0f, 3.0f, 1.0f }, ns_graphics::Light::LIGHT_TYPE::POINT);

			m_pCube1->setCamGameObject(m_pManager);
			m_pCube2->setCamGameObject(m_pManager);
			m_pCube3->setCamGameObject(m_pManager);
		}

		virtual void OnStateEnter() override {};

		virtual void OnStateExit() override {};
	};
}