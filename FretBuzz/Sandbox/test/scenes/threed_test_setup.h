#pragma once

#include <system/scene_manager.h>
#include <test/test_cube.h>
#include <framework/components/gameobject_components/camera.h>
#include <test/PlayerController.h>
#include <components/gameobject_components/canvas.h>
#include <components/gameobject_components/image.h>
#include <framework/graphics/model.h>
#include <test/PlayerController.h>

namespace ns_HMGame
{
	class threed_test_scene: public ns_fretBuzz::IScene
	{
	private:
		ns_fretBuzz::GameObject* m_pThreeDManager = nullptr;
		ns_HMGame::test_cube* m_pCube1 = nullptr;
		ns_HMGame::test_cube* m_pCube2 = nullptr;
		ns_HMGame::test_cube* m_pCube3 = nullptr;

		light_cube* m_pLightCube1 = nullptr;
		light_cube* m_pLightCube2 = nullptr;
		light_cube* m_pLightCube3 = nullptr;
		light_cube* m_pLightCube4 = nullptr;
		light_cube* m_pLightCube5 = nullptr;

		ns_fretBuzz::Model* m_pModel = nullptr;

	public:
		threed_test_scene(std::string a_strSceneName) 
			: IScene(a_strSceneName) 
		{
			ns_fretBuzz::GameObject* m_pManager = ns_fretBuzz::GameObject::instantiate(m_refRootGameObject, "3D_Manager", { 0.0f, 0.0f, 5.0f },
				{ 0.0f, M_PI, 0.0f }, { 1.0f, 1.0f, 1.0f });

			ns_fretBuzz::PerspectiveViewport l_PerspectiveViewport(60.0f, 1.0f, 50.0f);
			ns_fretBuzz::Camera* l_pMainCam = m_pManager->addComponent<ns_fretBuzz::Camera>(ns_fretBuzz::Viewport::PROJECTION_TYPE::PERSPECTIVE, &l_PerspectiveViewport, ns_fretBuzz::LayerMask(ns_fretBuzz::LayerMask::PREDEFINED_MASK::EVERYTHING));
			m_pManager->addComponent<ns_HMGame::PlayerController>();

			ns_fretBuzz::GameObject* m_pCam2GameObj = ns_fretBuzz::GameObject::instantiate(*m_pManager, "Cam2", { 0.0f, 0.0f, 0.0f },
					{ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
			ns_fretBuzz::PerspectiveViewport l_PerspectiveViewport2(60.0f, 1.0f, 50.0f, { 0.7, 0.7 }, { 0.3, 0.3 });
			ns_fretBuzz::Camera* l_pMainCam2 = m_pCam2GameObj->addComponent<ns_fretBuzz::Camera>(ns_fretBuzz::Viewport::PROJECTION_TYPE::PERSPECTIVE, &l_PerspectiveViewport2, ns_fretBuzz::LayerMask(ns_fretBuzz::LayerMask::PREDEFINED_MASK::EVERYTHING));

			ns_fretBuzz::GameObject* m_pNanoSuit = ns_fretBuzz::GameObject::instantiate(m_refRootGameObject, "NanoSuitMain", { 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
			ns_fretBuzz::Model::addToGameObject(*m_pNanoSuit, *ns_fretBuzz::ResourceManager::getResource<ns_fretBuzz::Model>("nanosuit//nanosuit.obj"));

			////Canvas Overlay
			//ns_fretBuzz::GameObject2D* m_pGameObjectUI = ns_fretBuzz::GameObject2D::instantiate(m_refRootGameObject, "Canvas", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 200.0f, 100.0f }, ns_fretBuzz::Layer());
			//ns_fretBuzz::ns_UI::CanvasData l_uiPlayerCanvasData;
			//l_uiPlayerCanvasData.m_CanvasSpaceType = ns_fretBuzz::ns_UI::CANVAS_SPACE_TYPE::SCREEN_SPACE_CAMERA;
			//l_uiPlayerCanvasData.m_pCamera = l_pMainCam;
			//l_uiPlayerCanvasData.m_fPlaneDistance = 1.05f;
			//ns_fretBuzz::ns_UI::Canvas* m_pCanvas = ns_fretBuzz::ns_UI::Canvas::addToGameObject(*m_pGameObjectUI, l_uiPlayerCanvasData);
			//ns_fretBuzz::GameObject2D* m_pImgWeapon = ns_fretBuzz::GameObject2D::instantiate(*m_pGameObjectUI, "img", { 0.5f, -0.5f, 0.0f }, { 0.0f, M_PI, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.3f, 0.3f }, ns_fretBuzz::Layer());
			//ns_fretBuzz::Image* m_pImage = ns_fretBuzz::Image::addToGameObject(*m_pImgWeapon, ns_fretBuzz::ResourceManager::getResource<ns_fretBuzz::SpriteGroup>("weapon_pickup|weapon_golf_club")->getSprite(0), { 0.0f, 0.0f, 0.0f, 1.0f });

			/*m_pCube2 = new test_cube(m_refRootGameObject, "Cube2", { 1.0f, 4.0f, 3.0f });
			m_pCube3 = new test_cube(m_refRootGameObject, "Cube3", { 2.0f, 0.0f, 0.0f });*/

			m_pLightCube1 = new light_cube(*m_pManager, "Light1", {0.0f, 0.0f, 0.0f}, ns_fretBuzz::Light::LIGHT_TYPE::SPOT, 1.0f);
			m_pLightCube2 = new light_cube(m_refRootGameObject, "Light2", { 1.0f, 3.0f, 1.0f }, ns_fretBuzz::Light::LIGHT_TYPE::POINT);
			m_pLightCube3 = new light_cube(m_refRootGameObject, "Light3", { 1.0f, 6.0f, 2.0f }, ns_fretBuzz::Light::LIGHT_TYPE::POINT);
			m_pLightCube4 = new light_cube(m_refRootGameObject, "Light4", { 1.0f, 9.0f, 3.0f }, ns_fretBuzz::Light::LIGHT_TYPE::POINT);
			m_pLightCube5 = new light_cube(m_refRootGameObject, "Light5", { 1.0f, 12.0f, 4.0f }, ns_fretBuzz::Light::LIGHT_TYPE::POINT);

			/*m_pCube2->setCamGameObject(m_pManager);
			m_pCube3->setCamGameObject(m_pManager);*/
			m_pCube1 = new test_cube(m_refRootGameObject, "Cube1", { -4.0f, 3.0f, -1.0f }, m_pNanoSuit);

			ns_fretBuzz::GameObject2D* m_pPlant0 = ns_fretBuzz::GameObject2D::instantiate(m_refRootGameObject, "Plant0", { 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, {2.0f, 2.0f});
			ns_fretBuzz::Image* l_pPlantImg0 = m_pPlant0->addComponent<ns_fretBuzz::Image>(nullptr, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

			ns_fretBuzz::GameObject2D* m_pPlant1 = ns_fretBuzz::GameObject2D::instantiate(m_refRootGameObject, "Plant1", { 5.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 2.0f, 2.0f });
			ns_fretBuzz::Image* l_pPlantImg1 = m_pPlant1->addComponent<ns_fretBuzz::Image>(nullptr, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

			ns_fretBuzz::GameObject2D* m_pPlant2 = ns_fretBuzz::GameObject2D::instantiate(m_refRootGameObject, "Plant2", { -5.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 2.0f, 2.0f });
			ns_fretBuzz::Image* l_pPlantImg2 = m_pPlant2->addComponent<ns_fretBuzz::Image>(nullptr, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
		}
	};
}