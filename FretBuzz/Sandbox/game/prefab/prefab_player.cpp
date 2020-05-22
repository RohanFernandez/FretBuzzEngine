#include <fretbuzz_pch.h>
#include "prefab_player.h"
#include "game/managers/player/PlayerControllerHM.h"
#include <components/gameobject_components/camera.h>
#include <system/camera_manager.h>

#include <components/gameobject_components/audio_source.h>

namespace ns_HMGame
{
	PrefabPlayer* PrefabPlayer::s_pInstance = nullptr;

	PrefabPlayer* PrefabPlayer::getInstance() { return s_pInstance; }

	PrefabPlayer::PrefabPlayer(ns_fretBuzz::ns_system::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH)
		: ns_fretBuzz::ns_system::GameObject2D(a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, ns_fretBuzz::ns_system::Layer("Player"), true)
	{
		ns_fretBuzz::ns_system::GameObject2D* l_pPlayerUpperGameObj = ns_fretBuzz::ns_system::GameObject2D::instantiate(*this, "PlayerUpper", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, ns_fretBuzz::ns_system::Layer("Player"), true);
		ns_fretBuzz::ns_system::GameObject2D* l_pPlayerLowerGameObj = ns_fretBuzz::ns_system::GameObject2D::instantiate(*this, "PlayerLegs", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, ns_fretBuzz::ns_system::Layer("Player"), true);
		ns_fretBuzz::ns_system::GameObject* l_pCamGameObj = &ns_fretBuzz::ns_graphics::CameraManager::get()->getMainCamera().m_GameObject;

		l_pPlayerLowerGameObj->addComponent<ns_fretBuzz::ns_system::SpriteAnimationController>("CharacterLegs");
		l_pPlayerUpperGameObj->addComponent<ns_fretBuzz::ns_system::SpriteAnimationController>("Player");

		ns_fretBuzz::ns_system::ColliderData l_RectColliderData;
		l_RectColliderData.m_PhysicsBodyType = ns_fretBuzz::ns_system::PHYSICS_BODY_TYPE::DYNAMIC;
		l_RectColliderData.m_usetColliderMaskBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_BOUNDARY);
		l_RectColliderData.m_usetColliderMaskBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_PICKUP);
		l_RectColliderData.m_usetColliderMaskBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_BULLET);
		l_RectColliderData.m_usetColliderCategoryBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_PLAYER);

		this->addComponent<ns_fretBuzz::ns_system::RectCollider>(l_RectColliderData);
		this->addComponent<PlayerControllerHM>(l_pCamGameObj, l_pPlayerUpperGameObj, l_pPlayerLowerGameObj);

		s_pInstance = this;
	}
}