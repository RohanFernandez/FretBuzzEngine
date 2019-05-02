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
#include "game/prefab/prefab_game_manager.h"

namespace ns_HMGame
{
	GameplayScene::GameplayScene(std::string a_strSceneName):
		ns_fretBuzz::ns_system::IScene(a_strSceneName)
	{
		ns_HMGame::PrefabGameManager* l_pGameManager = new ns_HMGame::PrefabGameManager(m_refRootGameObject, "GameManager");

		ns_fretBuzz::ns_system::GameObject* m_pCam = ns_fretBuzz::ns_system::GameObject::instantiate(m_refRootGameObject, "Main_Cam", { 0.0f, 0.0f , 0.0f }, { 0.0f, M_PI , 0.0f }, { 1.0f, 1.0f, 1.0f }, true);
		ns_fretBuzz::ns_graphics::OrthographicViewport l_CamViewport(-0.5f, 0.5f, -0.5f, 0.5f, -1.0f, 1.0f);
		ns_fretBuzz::ns_graphics::Camera* l_pCamComponent = ns_fretBuzz::ns_graphics::Camera::addToGameObject(*m_pCam, ns_fretBuzz::ns_graphics::Viewport::PROJECTION_TYPE::ORTHOGRAPHIC, &l_CamViewport);

		ns_fretBuzz::ns_system::Input::setCursorEnability(true, false);
		ns_fretBuzz::ns_system::GameObject2D* l_pCursor = ns_fretBuzz::ns_system::GameObject2D::instantiate(m_refRootGameObject, "Cursor", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 50.0f, 50.0f });
		ns_fretBuzz::ns_system::SpriteAnimationController::addToGameObject(*l_pCursor, "Cursor");
		ns_fretBuzz::ns_system::Behaviour::addToGameObject<CursorManager>(*l_pCursor, l_pCamComponent);

		ns_fretBuzz::ns_system::ColliderData l_RectColliderData;
		l_RectColliderData.m_vectColliderCategoryBits.emplace_back(ns_fretBuzz::ns_system::ColliderData::BIT_BOUNDARY);
		l_RectColliderData.m_vectColliderMaskBits.emplace_back(ns_fretBuzz::ns_system::ColliderData::BIT_PLAYER);

		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj1 = ns_fretBuzz::ns_system::GameObject2D::instantiate(m_refRootGameObject, "LABEL1", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
		ns_fretBuzz::ns_graphics::Image::addToGameObject(*l_pLabelGameObj1, nullptr, { 1.0f, 0.0f, 0.0f,1.0f }, true);
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*l_pLabelGameObj1, l_RectColliderData);

		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj2 = ns_fretBuzz::ns_system::GameObject2D::instantiate(*l_pLabelGameObj1, "LABEL2", { 50.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
		ns_fretBuzz::ns_graphics::Image::addToGameObject(*l_pLabelGameObj2, nullptr, { 0.0f, 1.0f, 0.0f,1.0f }, true);
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*l_pLabelGameObj2, l_RectColliderData);

		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj3 = ns_fretBuzz::ns_system::GameObject2D::instantiate(*l_pLabelGameObj2, "LABEL3", { 50.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
		ns_fretBuzz::ns_graphics::Image::addToGameObject(*l_pLabelGameObj3, nullptr, { 0.0f, 0.0f, 1.0f,1.0f }, true);
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*l_pLabelGameObj3, l_RectColliderData);

		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj4 = ns_fretBuzz::ns_system::GameObject2D::instantiate(*l_pLabelGameObj3, "LABEL4", { 50.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
		ns_fretBuzz::ns_graphics::Image::addToGameObject(*l_pLabelGameObj4, nullptr, { 1.0f, 1.0f, 0.0f,1.0f }, true);
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*l_pLabelGameObj4, l_RectColliderData);

		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj5 = ns_fretBuzz::ns_system::GameObject2D::instantiate(*l_pLabelGameObj4, "LABEL5", { 50.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
		ns_fretBuzz::ns_graphics::Image::addToGameObject(*l_pLabelGameObj5, nullptr, { 0.0f, 1.0f, 1.0f,1.0f }, true);
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*l_pLabelGameObj5, l_RectColliderData);

		/// Player
		ns_fretBuzz::ns_system::GameObject2D* m_pPlayerGameObject = new PrefabPlayer(m_refRootGameObject, "Player", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 40.0f, 40.0f });

		ns_fretBuzz::ns_system::GameObject2D* l_pPickupGameObj = ns_fretBuzz::ns_system::GameObject2D::instantiate(*l_pLabelGameObj4, "PICKUP", { 300.0f, 300.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
		ns_fretBuzz::ns_graphics::Image::addToGameObject(*l_pPickupGameObj, nullptr, { 1.0f, 1.0f, 1.0f, 1.0f }, true);

		ns_fretBuzz::ns_system::ColliderData l_SensorRectColliderData;
		l_SensorRectColliderData.m_bIsSensor = true;
		l_SensorRectColliderData.m_vectColliderCategoryBits.emplace_back(ns_fretBuzz::ns_system::ColliderData::BIT_PICKUP);
		l_SensorRectColliderData.m_vectColliderMaskBits.emplace_back(ns_fretBuzz::ns_system::ColliderData::BIT_PLAYER);
		l_SensorRectColliderData.m_PhysicsBodyType = ns_fretBuzz::ns_system::PhysicsEngine::PHYSICS_BODY_TYPE::STATIC;
		l_SensorRectColliderData.m_ColliderShape = ns_fretBuzz::ns_system::ColliderData::SHAPE_RECT;
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*l_pPickupGameObj, l_SensorRectColliderData);
	}
}