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

	PrefabPlayer::PrefabPlayer(FRETBUZZ::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH)
		: FRETBUZZ::GameObject2D(a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, "PLAYER")
	{
		FRETBUZZ::GameObject2D* l_pPlayerUpperGameObj = FRETBUZZ::GameObject2D::instantiate(*this, "PlayerUpper", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, "PLAYER", true);
		FRETBUZZ::GameObject2D* l_pPlayerLowerGameObj = FRETBUZZ::GameObject2D::instantiate(*this, "PlayerLegs", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, "PLAYER", true);
		FRETBUZZ::GameObject* l_pCamGameObj = &FRETBUZZ::CameraManager::get()->getMainCamera().m_GameObject;

		l_pPlayerLowerGameObj->addComponent<FRETBUZZ::SpriteAnimationController>("CharacterLegs");
		l_pPlayerUpperGameObj->addComponent<FRETBUZZ::SpriteAnimationController>("Player");

		FRETBUZZ::ColliderData l_RectColliderData;
		l_RectColliderData.m_PhysicsBodyType = FRETBUZZ::PHYSICS_BODY_TYPE::DYNAMIC;
		l_RectColliderData.m_CollisionMask.addLayers(std::vector<std::string>{"BOUNDARY", "PICKUP", "BULLET"});
		l_RectColliderData.m_CategoryMask.addLayers(std::vector<std::string>{"PLAYER"});

		this->addComponent<FRETBUZZ::RectCollider>(l_RectColliderData);
		this->addComponent<PlayerControllerHM>(l_pCamGameObj, l_pPlayerUpperGameObj, l_pPlayerLowerGameObj);

		s_pInstance = this;
	}
}