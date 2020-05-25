#include <fretbuzz_pch.h>
#include "prefab_wall.h"
#include <components/gameobject_components/image.h>
#include <game/managers/InteractiveObject.h>
#include <system/core/layer/layer_manager.h>

namespace ns_HMGame
{
	PrefabWall::PrefabWall(ns_fretBuzz::ns_system::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH)
		: ns_fretBuzz::ns_system::GameObject2D(a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH)
	{
		ns_fretBuzz::ns_system::ColliderData l_RectColliderData;

		l_RectColliderData.m_CategoryMask.addLayers(std::vector<std::string>{"BOUNDARY"});
		l_RectColliderData.m_CollisionMask.addLayers(std::vector<std::string>{"PLAYER", "ENEMY", "PICKUP", "BULLET"});
		l_RectColliderData.m_fFriction = 1.0f;

		this->addComponent<ns_fretBuzz::ns_graphics::Image>(nullptr, glm::vec4{ 1.0f, 0.0f, 0.0f,1.0f }, true);
		this->addComponent<ns_fretBuzz::ns_system::RectCollider>(l_RectColliderData);
	}
}