#include "fretbuzz_pch.h"
#include "gameplay_scene.h"
#include <system/core/input.h>
#include "components/gameobject_components/rect_collider.h"
#include "components/gameobject_components/audio_source.h"
#include "components//gameobject_components/image.h"
#include "../game/player/PlayerController.h"
#include "../game/cursor/cursor_manager.h"

#include <components/sprite.h>
#include "components/gameobject_components/sprite_animation_controller.h"

namespace ns_HMGame
{
	GameplayScene::GameplayScene(std::string a_strSceneName):
		ns_fretBuzz::ns_system::IScene(a_strSceneName)
	{
		ns_fretBuzz::ns_system::GameObject* l_pGameManager = ns_fretBuzz::ns_system::GameObject::instantiate(m_refRootGameObject, "GameManager", true);
		ns_fretBuzz::ns_system::AudioSource *l_pAudSrc = ns_fretBuzz::ns_system::AudioSource::addToGameObject(*l_pGameManager, "beats");
		l_pAudSrc->play();
		l_pAudSrc->setLooping(true);

		ns_fretBuzz::ns_system::GameObject* m_pCam = ns_fretBuzz::ns_system::GameObject::instantiate(m_refRootGameObject, "Main_Cam", { 0.0f, 0.0f , 0.0f }, { 0.0f, M_PI , 0.0f }, { 1.0f, 1.0f, 1.0f }, true);
		ns_fretBuzz::ns_graphics::OrthographicViewport l_CamViewport(-0.5f, 0.5f, -0.5f, 0.5f, -1.0f, 1.0f);
		ns_fretBuzz::ns_graphics::Camera* l_pCamComponent = ns_fretBuzz::ns_graphics::Camera::addToGameObject(*m_pCam, ns_fretBuzz::ns_graphics::Viewport::PROJECTION_TYPE::ORTHOGRAPHIC, &l_CamViewport);

		ns_fretBuzz::ns_system::Input::setCursorEnability(false);
		ns_fretBuzz::ns_system::GameObject2D* l_pCursor = ns_fretBuzz::ns_system::GameObject2D::instantiate(m_refRootGameObject, "Cursor", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 50.0f, 50.0f });
		ns_fretBuzz::ns_system::SpriteAnimationController::addToGameObject(*l_pCursor, "Cursor");
		ns_fretBuzz::ns_system::Behaviour::addToGameObject<CursorManager>(*l_pCursor, l_pCamComponent);

		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj1 = ns_fretBuzz::ns_system::GameObject2D::instantiate(m_refRootGameObject, "LABEL1", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
		ns_fretBuzz::ns_graphics::Image::addToGameObject(*l_pLabelGameObj1, nullptr, { 1.0f, 0.0f, 0.0f,1.0f }, true);
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*l_pLabelGameObj1);

		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj2 = ns_fretBuzz::ns_system::GameObject2D::instantiate(*l_pLabelGameObj1, "LABEL2", { 50.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
		ns_fretBuzz::ns_graphics::Image::addToGameObject(*l_pLabelGameObj2, nullptr, { 0.0f, 1.0f, 0.0f,1.0f }, true);
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*l_pLabelGameObj2);

		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj3 = ns_fretBuzz::ns_system::GameObject2D::instantiate(*l_pLabelGameObj2, "LABEL3", { 50.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
		ns_fretBuzz::ns_graphics::Image::addToGameObject(*l_pLabelGameObj3, nullptr, { 0.0f, 0.0f, 1.0f,1.0f }, true);
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*l_pLabelGameObj3);

		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj4 = ns_fretBuzz::ns_system::GameObject2D::instantiate(*l_pLabelGameObj3, "LABEL4", { 50.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
		ns_fretBuzz::ns_graphics::Image::addToGameObject(*l_pLabelGameObj4, nullptr, { 1.0f, 1.0f, 0.0f,1.0f }, true);
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*l_pLabelGameObj4);

		ns_fretBuzz::ns_system::GameObject2D* l_pLabelGameObj5 = ns_fretBuzz::ns_system::GameObject2D::instantiate(*l_pLabelGameObj4, "LABEL5", { 50.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
		ns_fretBuzz::ns_graphics::Image::addToGameObject(*l_pLabelGameObj5, nullptr, { 0.0f, 1.0f, 1.0f,1.0f }, true);
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*l_pLabelGameObj5);

		/// Player
		ns_fretBuzz::ns_system::GameObject2D* m_pPlayerGameObject = ns_fretBuzz::ns_system::GameObject2D::instantiate(m_refRootGameObject, "Player", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 150.0f, 100.0f }, true);
		ns_fretBuzz::ns_system::GameObject2D* m_pPlayerLegsGameObject = ns_fretBuzz::ns_system::GameObject2D::instantiate(*m_pPlayerGameObject, "PlayerLegs", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, true);

		ns_fretBuzz::ns_system::SpriteAnimationController::addToGameObject(*m_pPlayerLegsGameObject, "CharacterLegs");
		ns_fretBuzz::ns_system::SpriteAnimationController::addToGameObject(*m_pPlayerGameObject, "Player");

		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*m_pPlayerGameObject, { 50.0f, 50.0f }, ns_fretBuzz::ns_system::PhysicsEngine::PHYSICS_BODY_TYPE::DYNAMIC, true);
		ns_fretBuzz::ns_system::Behaviour::addToGameObject<PlayerController>(*m_pPlayerGameObject, m_pCam, m_pPlayerLegsGameObject);
	}
}