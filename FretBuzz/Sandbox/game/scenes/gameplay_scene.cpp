#include "fretbuzz_pch.h"
#include "gameplay_scene.h"
#include <input.h>
#include <components/gameobject_components/rect_collider.h>
#include <components/gameobject_components/audio_source.h>
#include <components/gameobject_components/image.h>
#include <game/managers/player/PlayerControllerHM.h>
#include <game/managers/cursor/cursor_manager.h>
		 
#include <components/sprite.h>
#include <components/gameobject_components/sprite_animation_controller.h>
#include <game/prefab/prefab_player.h>
#include <game/prefab/prefab_wall.h>
#include <game/prefab/prefab_game_manager.h>
#include <game/prefab/prefab_weapon.h>
#include <game/managers/weapon/weapon_manager.h>
#include <game/prefab/prefab_enemy.h>
#include <components/gameobject_components/canvas.h>
#include <resource_manager.h>
#include <components/gameobject_components/text_renderer.h>

namespace ns_HMGame
{
	GameplayScene::GameplayScene(std::string a_strSceneName):
		FRETBUZZ::IScene(a_strSceneName)
	{
		PrefabGameManager* l_pGameManager = new PrefabGameManager(m_refRootGameObject, "GameManager");

		FRETBUZZ::GameObject* m_pCam = FRETBUZZ::GameObject::instantiate(m_refRootGameObject, "Main_Cam", { 0.0f, 0.0f , 0.0f }, { 0.0f, M_PI , 0.0f }, { 1.0f, 1.0f, 1.0f });
		FRETBUZZ::OrthographicViewport l_CamViewport(-1.0f, 1.0f);
		FRETBUZZ::Camera* l_pCamComponent = m_pCam->addComponent<FRETBUZZ::Camera>(FRETBUZZ::Viewport::PROJECTION_TYPE::ORTHOGRAPHIC, &l_CamViewport, FRETBUZZ::LayerMask(FRETBUZZ::LayerMask::PREDEFINED_MASK::EVERYTHING), glm::vec4{ 70.0/255.0f, 114.0f/255.0f, 136.0f/255.0f,1.0f});
		
		/*FRETBUZZ::GameObject2D* m_pGameObjectUI = FRETBUZZ::GameObject2D::instantiate(m_refRootGameObject, "Canvas", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f },{ 200.0f, 100.0f }, FRETBUZZ::Layer());
		FRETBUZZ::ns_UI::CanvasData l_uiPlayerCanvasData;
		l_uiPlayerCanvasData.m_CanvasSpaceType = FRETBUZZ::ns_UI::CANVAS_SPACE_TYPE::SCREEN_SPACE_OVERLAY;
		l_uiPlayerCanvasData.m_pCamera = l_pCamComponent;
		FRETBUZZ::ns_UI::Canvas* m_pCanvas = FRETBUZZ::ns_UI::Canvas::addToGameObject(*m_pGameObjectUI, l_uiPlayerCanvasData);
		FRETBUZZ::GameObject2D* m_pImgWeapon = FRETBUZZ::GameObject2D::instantiate(*m_pGameObjectUI, "img", { -300.0f, -250.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 200.0f, 100.0f }, FRETBUZZ::Layer());
		FRETBUZZ::Image* m_pImage = FRETBUZZ::Image::addToGameObject(*m_pImgWeapon, FRETBUZZ::ResourceManager::getResource<FRETBUZZ::SpriteGroup>("weapon_pickup|weapon_golf_club")->getSprite(0), { 0.0f, 0.0f, 0.0f, 1.0f });
		FRETBUZZ::TextRenderer* m_pTxtRnd = FRETBUZZ::TextRenderer::addToGameObject(*m_pImgWeapon, "asd", "Cousine-Regular");*/


		FRETBUZZ::GameObject* m_pCam2 = FRETBUZZ::GameObject::instantiate(*m_pCam, "Camera2", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f });
		FRETBUZZ::OrthographicViewport l_CamViewport2(-0.5, 0.5, -0.5, 0.5, -1.0f, 1.0f, {0.7f, 0.7f}, {0.3f, 0.3 });
		FRETBUZZ::Camera* l_pCamComponent2 = m_pCam2->addComponent<FRETBUZZ::Camera>(FRETBUZZ::Viewport::PROJECTION_TYPE::ORTHOGRAPHIC, &l_CamViewport2, FRETBUZZ::LayerMask(FRETBUZZ::LayerMask::PREDEFINED_MASK::EVERYTHING), glm::vec4{ 225.0f / 255.0f, 95.0f / 255.0f, 60.0f/255.0f,1.0f });


		FRETBUZZ::Input::setCursorEnability(true, false);
		FRETBUZZ::GameObject2D* l_pCursor = FRETBUZZ::GameObject2D::instantiate(m_refRootGameObject, "Cursor", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 50.0f, 50.0f });
		l_pCursor->addComponent<FRETBUZZ::SpriteAnimationController>("Cursor");
		l_pCursor->addComponent<CursorManager>(l_pCamComponent);

		FRETBUZZ::GameObject2D* l_pLabelGameObj1 = new PrefabWall(m_refRootGameObject, "WALL1", {   0.0f,   30.0f, 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 400.0f, 100.0f });
		FRETBUZZ::GameObject2D* l_pLabelGameObj2 = new PrefabWall(m_refRootGameObject, "WALL2", { 150.0f, -130.0f, 0.0f }, { 0.0f, 0.0f , 0.0f}, { 1.0f, 1.0f, 1.0f }, { 100.0f, 300.0f });
		FRETBUZZ::GameObject2D* l_pLabelGameObj3 = new PrefabWall(m_refRootGameObject, "WALL3", {-200.0f, -330.0f, 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 800.0f, 100.0f });
		FRETBUZZ::GameObject2D* l_pLabelGameObj4 = new PrefabWall(m_refRootGameObject, "WALL4", { -550.0f, -130.0f, 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 100.0f, 300.0f });

		/// Player
		FRETBUZZ::GameObject2D* m_pPlayerGameObject = new PrefabPlayer(m_refRootGameObject, "Player", { 0.0f, -100.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 40.0f, 40.0f });

		/// Enemy
		FRETBUZZ::GameObject2D* m_pEnemyGameObject1 = new PrefabEnemy(m_refRootGameObject, "Enemy1", { 0.0f, -200.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 40.0f, 40.0f });
		FRETBUZZ::GameObject2D* m_pEnemyGameObject2 = new PrefabEnemy(m_refRootGameObject, "Enemy2", { 300.0f, 200.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 40.0f, 40.0f });

		//FRETBUZZ::GameObject2D* l_pPickupGameObj = new ns_HMGame::PrefabWeapon(&m_refRootGameObject, "WEAPON", { -375.0f, -100.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 70.0f, 70.0f });

		WeaponManager::AddWeapon({ -200.0f, 200.0f , 0.0f }, WEAPON_DOUBLE_BARREL, true);
		WeaponManager::AddWeapon({ -300.0f, 70.0f , 0.0f }, WEAPON_M16, true);
	}
}