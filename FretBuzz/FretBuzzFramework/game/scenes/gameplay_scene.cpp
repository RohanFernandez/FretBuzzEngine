#include "fretbuzz_pch.h"
#include "gameplay_scene.h"
#include <system/core/input.h>
#include "components/gameobject_components/rect_collider.h"
#include "components/gameobject_components/audio_source.h"
#include "components//gameobject_components/image.h"
#include "game/managers/player/PlayerController.h"
#include "game/managers/cursor/cursor_manager.h"

#include <components/sprite.h>
#include "components/gameobject_components/sprite_animation_controller.h"

#include "game/prefab/prefab_player.h"
#include "game/prefab/prefab_wall.h"
#include "game/prefab/prefab_game_manager.h"
#include "game/prefab/prefab_weapon.h"
#include "game/managers/weapon/weapon_manager.h"
#include "game/prefab/prefab_enemy.h"
#include "components/gameobject_components/canvas.h"
#include "system/core/resource_manager.h"

namespace ns_HMGame
{
	GameplayScene::GameplayScene(std::string a_strSceneName):
		ns_fretBuzz::ns_system::IScene(a_strSceneName)
	{
		ns_HMGame::PrefabGameManager* l_pGameManager = new ns_HMGame::PrefabGameManager(m_refRootGameObject, "GameManager");

		ns_fretBuzz::ns_system::GameObject* m_pCam = ns_fretBuzz::ns_system::GameObject::instantiate(m_refRootGameObject, "Main_Cam", { 0.0f, 0.0f , 0.0f }, { 0.0f, M_PI , 0.0f }, { 1.0f, 1.0f, 1.0f }, true);
		ns_fretBuzz::ns_graphics::OrthographicViewport l_CamViewport(-0.5f, 0.5f, -0.5f, 0.5f, -1.0f, 1.0f);
		ns_fretBuzz::ns_graphics::Camera* l_pCamComponent = ns_fretBuzz::ns_graphics::Camera::addToGameObject(*m_pCam, ns_fretBuzz::ns_graphics::Viewport::PROJECTION_TYPE::ORTHOGRAPHIC, &l_CamViewport);
		
		ns_fretBuzz::ns_system::GameObject2D* m_pGameObjectUI = ns_fretBuzz::ns_system::GameObject2D::instantiate(m_refRootGameObject, "Canvas", { -300.0f, -250.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f },{ 200.0f, 100.0f });
		ns_fretBuzz::ns_UI::CanvasData l_uiPlayerCanvasData;
		l_uiPlayerCanvasData.m_CanvasSpaceType = ns_fretBuzz::ns_UI::CANVAS_SPACE_TYPE::SCREEN_SPACE_OVERLAY;
		l_uiPlayerCanvasData.m_pCamera = l_pCamComponent;
		ns_fretBuzz::ns_UI::Canvas* m_pCanvas = ns_fretBuzz::ns_UI::Canvas::addToGameObject(*m_pGameObjectUI, l_uiPlayerCanvasData);
		ns_fretBuzz::ns_system::GameObject2D* m_pImgWeapon = ns_fretBuzz::ns_system::GameObject2D::instantiate(*m_pGameObjectUI, "img", { 300.0f, -250.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 200.0f, 100.0f });
		ns_fretBuzz::ns_graphics::Image* m_pImage = ns_fretBuzz::ns_graphics::Image::addToGameObject(*m_pImgWeapon, ns_fretBuzz::ns_system::ResourceManager::getResource<ns_fretBuzz::ns_graphics::SpriteGroup>("weapon_pickup|weapon_golf_club")->getSprite(0), { 0.0f, 0.0f, 0.0f, 1.0f });

		ns_fretBuzz::ns_system::Input::setCursorEnability(true, false);
		ns_fretBuzz::ns_system::GameObject2D* l_pCursor = ns_fretBuzz::ns_system::GameObject2D::instantiate(m_refRootGameObject, "Cursor", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 50.0f, 50.0f });
		ns_fretBuzz::ns_system::SpriteAnimationController::addToGameObject(*l_pCursor, "Cursor");
		ns_fretBuzz::ns_system::Behaviour::addToGameObject<CursorManager>(l_pCursor, l_pCamComponent);

		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj1 = new ns_HMGame::PrefabWall(m_refRootGameObject, "WALL1", {   0.0f,   30.0f, 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 400.0f, 100.0f });
		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj2 = new ns_HMGame::PrefabWall(m_refRootGameObject, "WALL2", { 150.0f, -130.0f, 0.0f }, { 0.0f, 0.0f , 0.0f}, { 1.0f, 1.0f, 1.0f }, { 100.0f, 300.0f });
		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj3 = new ns_HMGame::PrefabWall(m_refRootGameObject, "WALL3", {-200.0f, -330.0f, 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 800.0f, 100.0f });
		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj4 = new ns_HMGame::PrefabWall(m_refRootGameObject, "WALL4", { -550.0f, -130.0f, 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 100.0f, 300.0f });

		/// Player
		ns_fretBuzz::ns_system::GameObject2D* m_pPlayerGameObject = new PrefabPlayer(m_refRootGameObject, "Player", { 0.0f, -100.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 40.0f, 40.0f });

		/// Enemy
		ns_fretBuzz::ns_system::GameObject2D* m_pEnemyGameObject1 = new PrefabEnemy(m_refRootGameObject, "Enemy1", { 0.0f, -200.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 40.0f, 40.0f });
		ns_fretBuzz::ns_system::GameObject2D* m_pEnemyGameObject2 = new PrefabEnemy(m_refRootGameObject, "Enemy2", { 300.0f, 200.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 40.0f, 40.0f });

		//ns_fretBuzz::ns_system::GameObject2D* l_pPickupGameObj = new ns_HMGame::PrefabWeapon(&m_refRootGameObject, "WEAPON", { -375.0f, -100.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 70.0f, 70.0f });

		WeaponManager::AddWeapon({ -200.0f, 200.0f , 0.0f }, WEAPON_DOUBLE_BARREL, true);
		WeaponManager::AddWeapon({ -300.0f, 70.0f , 0.0f }, WEAPON_M16, true);
	}
}