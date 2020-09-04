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
	class threed_test_scene: public FRETBUZZ::IScene
	{
	private:
		FRETBUZZ::GameObject* m_pThreeDManager = nullptr;
		ns_HMGame::test_cube* m_pCube1 = nullptr;
		ns_HMGame::test_cube* m_pCube2 = nullptr;
		ns_HMGame::test_cube* m_pCube3 = nullptr;

		light_cube* m_pLightCube1 = nullptr;
		light_cube* m_pLightCube2 = nullptr;
		light_cube* m_pLightCube3 = nullptr;
		light_cube* m_pLightCube4 = nullptr;
		light_cube* m_pLightCube5 = nullptr;

		FRETBUZZ::Model* m_pModel = nullptr;

	public:
		threed_test_scene(std::string a_strSceneName) 
			: IScene(a_strSceneName) 
		{
			FRETBUZZ::GameObject* m_pManager = FRETBUZZ::GameObject::instantiate(m_refRootGameObject, "3D_Manager", { 0.0f, 0.0f, 5.0f },
				{ 0.0f, M_PI, 0.0f }, { 1.0f, 1.0f, 1.0f });

			FRETBUZZ::PerspectiveViewport l_PerspectiveViewport(60.0f, 1.0f, 50.0f);
			FRETBUZZ::Camera* l_pMainCam = m_pManager->addComponent<FRETBUZZ::Camera>(FRETBUZZ::Viewport::PROJECTION_TYPE::PERSPECTIVE, &l_PerspectiveViewport, FRETBUZZ::LayerMask(FRETBUZZ::LayerMask::PREDEFINED_MASK::EVERYTHING));
			m_pManager->addComponent<ns_HMGame::PlayerController>();

			FRETBUZZ::GameObject* m_pCam2GameObj = FRETBUZZ::GameObject::instantiate(*m_pManager, "Cam2", { 0.0f, 0.0f, 0.0f },
					{ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
			FRETBUZZ::PerspectiveViewport l_PerspectiveViewport2(60.0f, 1.0f, 50.0f, { 0.7, 0.7 }, { 0.3, 0.3 });
			FRETBUZZ::Camera* l_pMainCam2 = m_pCam2GameObj->addComponent<FRETBUZZ::Camera>(FRETBUZZ::Viewport::PROJECTION_TYPE::PERSPECTIVE, &l_PerspectiveViewport2, FRETBUZZ::LayerMask(FRETBUZZ::LayerMask::PREDEFINED_MASK::EVERYTHING));

			FRETBUZZ::GameObject* m_pNanoSuit = FRETBUZZ::GameObject::instantiate(m_refRootGameObject, "NanoSuitMain", { 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
			FRETBUZZ::Model::addToGameObject(*m_pNanoSuit, *FRETBUZZ::ResourceManager::getResource<FRETBUZZ::Model>("nanosuit//nanosuit.obj"));

			////Canvas Overlay
			//FRETBUZZ::GameObject2D* m_pGameObjectUI = FRETBUZZ::GameObject2D::instantiate(m_refRootGameObject, "Canvas", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 200.0f, 100.0f }, FRETBUZZ::Layer());
			//FRETBUZZ::ns_UI::CanvasData l_uiPlayerCanvasData;
			//l_uiPlayerCanvasData.m_CanvasSpaceType = FRETBUZZ::ns_UI::CANVAS_SPACE_TYPE::SCREEN_SPACE_CAMERA;
			//l_uiPlayerCanvasData.m_pCamera = l_pMainCam;
			//l_uiPlayerCanvasData.m_fPlaneDistance = 1.05f;
			//FRETBUZZ::ns_UI::Canvas* m_pCanvas = FRETBUZZ::ns_UI::Canvas::addToGameObject(*m_pGameObjectUI, l_uiPlayerCanvasData);
			//FRETBUZZ::GameObject2D* m_pImgWeapon = FRETBUZZ::GameObject2D::instantiate(*m_pGameObjectUI, "img", { 0.5f, -0.5f, 0.0f }, { 0.0f, M_PI, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.3f, 0.3f }, FRETBUZZ::Layer());
			//FRETBUZZ::Image* m_pImage = FRETBUZZ::Image::addToGameObject(*m_pImgWeapon, FRETBUZZ::ResourceManager::getResource<FRETBUZZ::SpriteGroup>("weapon_pickup|weapon_golf_club")->getSprite(0), { 0.0f, 0.0f, 0.0f, 1.0f });

			/*m_pCube2 = new test_cube(m_refRootGameObject, "Cube2", { 1.0f, 4.0f, 3.0f });
			m_pCube3 = new test_cube(m_refRootGameObject, "Cube3", { 2.0f, 0.0f, 0.0f });*/

			m_pLightCube1 = new light_cube(*m_pManager, "Light1", {0.0f, 0.0f, 0.0f}, FRETBUZZ::Light::LIGHT_TYPE::SPOT, 1.0f);
			m_pLightCube2 = new light_cube(m_refRootGameObject, "Light2", { 1.0f, 3.0f, 1.0f }, FRETBUZZ::Light::LIGHT_TYPE::POINT);
			m_pLightCube3 = new light_cube(m_refRootGameObject, "Light3", { 1.0f, 6.0f, 2.0f }, FRETBUZZ::Light::LIGHT_TYPE::POINT);
			m_pLightCube4 = new light_cube(m_refRootGameObject, "Light4", { 1.0f, 9.0f, 3.0f }, FRETBUZZ::Light::LIGHT_TYPE::POINT);
			m_pLightCube5 = new light_cube(m_refRootGameObject, "Light5", { 1.0f, 12.0f, 4.0f }, FRETBUZZ::Light::LIGHT_TYPE::POINT);

			/*m_pCube2->setCamGameObject(m_pManager);
			m_pCube3->setCamGameObject(m_pManager);*/
			m_pCube1 = new test_cube(m_refRootGameObject, "Cube1", { -4.0f, 3.0f, -1.0f }, m_pNanoSuit);

			FRETBUZZ::GameObject2D* m_pPlant0 = FRETBUZZ::GameObject2D::instantiate(m_refRootGameObject, "Plant0", { 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, {2.0f, 2.0f});
			FRETBUZZ::Image* l_pPlantImg0 = m_pPlant0->addComponent<FRETBUZZ::Image>(nullptr, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

			FRETBUZZ::GameObject2D* m_pPlant1 = FRETBUZZ::GameObject2D::instantiate(m_refRootGameObject, "Plant1", { 5.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 2.0f, 2.0f });
			FRETBUZZ::Image* l_pPlantImg1 = m_pPlant1->addComponent<FRETBUZZ::Image>(nullptr, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

			FRETBUZZ::GameObject2D* m_pPlant2 = FRETBUZZ::GameObject2D::instantiate(m_refRootGameObject, "Plant2", { -5.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 2.0f, 2.0f });
			FRETBUZZ::Image* l_pPlantImg2 = m_pPlant2->addComponent<FRETBUZZ::Image>(nullptr, glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
		}
	};
}