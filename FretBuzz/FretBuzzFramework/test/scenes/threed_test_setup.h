#pragma once
#include "framework/system/scene_manager.h"

#include "framework/components/gameobject_components/camera.h"
#include "test/PlayerController.h"
#include "test/test_cube.h"
#include "components/gameobject_components/canvas.h"

#include "framework/graphics/model.h"

namespace ns_fretBuzz
{
	class FRETBUZZ_API threed_test_scene:
		public ns_system::IScene
	{
	private:
		ns_system::GameObject* m_pThreeDManager = nullptr;
		test_cube* m_pCube1 = nullptr;
		test_cube* m_pCube2 = nullptr;
		test_cube* m_pCube3 = nullptr;

		light_cube* m_pLightCube1 = nullptr;
		light_cube* m_pLightCube2 = nullptr;
		light_cube* m_pLightCube3 = nullptr;
		light_cube* m_pLightCube4 = nullptr;
		light_cube* m_pLightCube5 = nullptr;

		ns_graphics::Model* m_pModel = nullptr;

	public:
		threed_test_scene(std::string a_strSceneName) 
			: IScene(a_strSceneName) 
		{
			ns_system::GameObject* m_pManager = ns_system::GameObject::instantiate(m_refRootGameObject, "3D_Manager", { 0.0f, 0.0f, 5.0f },
				{ 0.0f, M_PI, 0.0f }, { 1.0f, 1.0f, 1.0f }, ns_fretBuzz::ns_system::Layer());

			ns_graphics::PerspectiveViewport l_PerspectiveViewport(60.0f, 1.0f, 50.0f);
			ns_graphics::Camera* l_pMainCam = m_pManager->addComponent<ns_graphics::Camera>(ns_graphics::Viewport::PROJECTION_TYPE::PERSPECTIVE, &l_PerspectiveViewport,ns_system::LayerMask());
			m_pManager->addComponent<PlayerController>();

			ns_system::GameObject* m_pCam2GameObj = ns_system::GameObject::instantiate(*m_pManager, "Cam2", { 0.0f, 0.0f, 0.0f },
					{ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, ns_fretBuzz::ns_system::Layer());
			ns_graphics::PerspectiveViewport l_PerspectiveViewport2(60.0f, 1.0f, 50.0f, { 0.7, 0.7 }, { 0.3, 0.3 });
			ns_graphics::Camera* l_pMainCam2 = m_pCam2GameObj->addComponent<ns_graphics::Camera>(ns_graphics::Viewport::PROJECTION_TYPE::PERSPECTIVE, &l_PerspectiveViewport2, ns_system::LayerMask());

			ns_system::GameObject* m_pNanoSuit = ns_system::GameObject::instantiate(m_refRootGameObject, "NanoSuitMain", { 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, ns_fretBuzz::ns_system::Layer());
			ns_graphics::Model::addToGameObject(*m_pNanoSuit, *ns_system::ResourceManager::getResource<ns_graphics::Model>("nanosuit//nanosuit.obj"));

			////Canvas Overlay
			//ns_fretBuzz::ns_system::GameObject2D* m_pGameObjectUI = ns_fretBuzz::ns_system::GameObject2D::instantiate(m_refRootGameObject, "Canvas", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 200.0f, 100.0f }, ns_fretBuzz::ns_system::Layer());
			//ns_fretBuzz::ns_UI::CanvasData l_uiPlayerCanvasData;
			//l_uiPlayerCanvasData.m_CanvasSpaceType = ns_fretBuzz::ns_UI::CANVAS_SPACE_TYPE::SCREEN_SPACE_CAMERA;
			//l_uiPlayerCanvasData.m_pCamera = l_pMainCam;
			//l_uiPlayerCanvasData.m_fPlaneDistance = 1.05f;
			//ns_fretBuzz::ns_UI::Canvas* m_pCanvas = ns_fretBuzz::ns_UI::Canvas::addToGameObject(*m_pGameObjectUI, l_uiPlayerCanvasData);
			//ns_fretBuzz::ns_system::GameObject2D* m_pImgWeapon = ns_fretBuzz::ns_system::GameObject2D::instantiate(*m_pGameObjectUI, "img", { 0.5f, -0.5f, 0.0f }, { 0.0f, M_PI, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.3f, 0.3f }, ns_fretBuzz::ns_system::Layer());
			//ns_fretBuzz::ns_graphics::Image* m_pImage = ns_fretBuzz::ns_graphics::Image::addToGameObject(*m_pImgWeapon, ns_fretBuzz::ns_system::ResourceManager::getResource<ns_fretBuzz::ns_graphics::SpriteGroup>("weapon_pickup|weapon_golf_club")->getSprite(0), { 0.0f, 0.0f, 0.0f, 1.0f });

			/*m_pCube2 = new test_cube(m_refRootGameObject, "Cube2", { 1.0f, 4.0f, 3.0f });
			m_pCube3 = new test_cube(m_refRootGameObject, "Cube3", { 2.0f, 0.0f, 0.0f });*/

			m_pLightCube1 = new light_cube(*m_pManager, "Light1", {0.0f, 0.0f, 0.0f}, ns_graphics::Light::LIGHT_TYPE::SPOT, 1.0f);
			m_pLightCube2 = new light_cube(m_refRootGameObject, "Light2", { 1.0f, 3.0f, 1.0f }, ns_graphics::Light::LIGHT_TYPE::POINT);
			m_pLightCube3 = new light_cube(m_refRootGameObject, "Light3", { 1.0f, 6.0f, 2.0f }, ns_graphics::Light::LIGHT_TYPE::POINT);
			m_pLightCube4 = new light_cube(m_refRootGameObject, "Light4", { 1.0f, 9.0f, 3.0f }, ns_graphics::Light::LIGHT_TYPE::POINT);
			m_pLightCube5 = new light_cube(m_refRootGameObject, "Light5", { 1.0f, 12.0f, 4.0f }, ns_graphics::Light::LIGHT_TYPE::POINT);

			/*m_pCube2->setCamGameObject(m_pManager);
			m_pCube3->setCamGameObject(m_pManager);*/
			m_pCube1 = new test_cube(m_refRootGameObject, "Cube1", { -4.0f, 3.0f, -1.0f }, m_pNanoSuit);

			//ns_system::GameObject* m_pAudi = ns_system::GameObject::instantiate(m_refRootGameObject, "DeskMain");
			//ns_graphics::Model::addToGameObject(*m_pAudi, *ns_system::ResourceManager::getResource<ns_graphics::Model>("FruitNinja_env//FruitNinja_Env.FBX"));

			ns_system::GameObject2D* m_pPlant0 = ns_system::GameObject2D::instantiate(m_refRootGameObject, "Plant0", { 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, {2.0f, 2.0f}, ns_fretBuzz::ns_system::Layer());
			ns_graphics::Image* l_pPlantImg0 = m_pPlant0->addComponent<ns_graphics::Image>(nullptr, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

			ns_system::GameObject2D* m_pPlant1 = ns_system::GameObject2D::instantiate(m_refRootGameObject, "Plant1", { 5.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 2.0f, 2.0f }, ns_fretBuzz::ns_system::Layer());
			ns_graphics::Image* l_pPlantImg1 = m_pPlant1->addComponent<ns_graphics::Image>(nullptr, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

			ns_system::GameObject2D* m_pPlant2 = ns_system::GameObject2D::instantiate(m_refRootGameObject, "Plant2", { -5.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 2.0f, 2.0f }, ns_fretBuzz::ns_system::Layer());
			ns_graphics::Image* l_pPlantImg2 = m_pPlant2->addComponent<ns_graphics::Image>(nullptr, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
		}
	};
}