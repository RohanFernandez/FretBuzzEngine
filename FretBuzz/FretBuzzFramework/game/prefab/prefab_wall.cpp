#include <fretbuzz_pch.h>
#include "prefab_wall.h"
#include <components/gameobject_components/image.h>
#include <game/managers/InteractiveObject.h>

namespace ns_HMGame
{
	PrefabWall::PrefabWall(ns_fretBuzz::ns_system::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH)
		: ns_fretBuzz::ns_system::GameObject2D(a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, true)
	{
		ns_fretBuzz::ns_system::ColliderData l_RectColliderData;
		l_RectColliderData.m_usetColliderCategoryBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_BOUNDARY);
		l_RectColliderData.m_usetColliderMaskBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_PLAYER);
		l_RectColliderData.m_usetColliderMaskBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_PICKUP);
		l_RectColliderData.m_usetColliderMaskBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_BULLET);
		l_RectColliderData.m_fFriction = 1.0f;

		ns_fretBuzz::ns_graphics::Image::addToGameObject(*this, nullptr, { 1.0f, 0.0f, 0.0f,1.0f }, true);
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*this, l_RectColliderData);
	}
}