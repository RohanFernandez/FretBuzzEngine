#include <fretbuzz_pch.h>
#include "prefab_player.h"
#include "game/managers/player/PlayerController.h"
#include <components/gameobject_components/camera.h>
#include <system/camera_manager.h>

#include <components/gameobject_components/audio_source.h>

namespace ns_HMGame
{
	PrefabPlayer::PrefabPlayer(ns_fretBuzz::ns_system::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH)
		: ns_fretBuzz::ns_system::GameObject2D(a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, true)
	{
		ns_fretBuzz::ns_system::GameObject2D* l_pPlayerUpperGameObj = ns_fretBuzz::ns_system::GameObject2D::instantiate(*this, "PlayerUpper", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, true);
		ns_fretBuzz::ns_system::GameObject2D* l_pPlayerLowerGameObj = ns_fretBuzz::ns_system::GameObject2D::instantiate(*this, "PlayerLegs", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, true);
		ns_fretBuzz::ns_system::GameObject* l_pCamGameObj = &ns_fretBuzz::ns_graphics::CameraManager::get()->getMainCamera().m_GameObject;

		ns_fretBuzz::ns_system::SpriteAnimationController::addToGameObject(*l_pPlayerLowerGameObj, "CharacterLegs");
		ns_fretBuzz::ns_system::SpriteAnimationController::addToGameObject(*l_pPlayerUpperGameObj, "Player");

		ns_fretBuzz::ns_system::ColliderData l_RectColliderData;
		l_RectColliderData.m_PhysicsBodyType = ns_fretBuzz::ns_system::PhysicsEngine::PHYSICS_BODY_TYPE::DYNAMIC;
		l_RectColliderData.m_vectColliderMaskBits.emplace_back(ns_fretBuzz::ns_system::ColliderData::BIT_BOUNDARY);
		l_RectColliderData.m_vectColliderMaskBits.emplace_back(ns_fretBuzz::ns_system::ColliderData::BIT_PICKUP);

		l_RectColliderData.m_vectColliderCategoryBits.emplace_back(ns_fretBuzz::ns_system::ColliderData::BIT_PLAYER);

		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*this, l_RectColliderData);
		ns_fretBuzz::ns_system::Behaviour::addToGameObject<PlayerController>(*this, l_pCamGameObj, l_pPlayerUpperGameObj, l_pPlayerLowerGameObj);
	}
}