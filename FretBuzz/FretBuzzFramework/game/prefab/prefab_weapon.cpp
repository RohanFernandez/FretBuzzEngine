#include <fretbuzz_pch.h>
#include "prefab_weapon.h"
#include <game/managers/weapon/weapon.h>
#include <components/gameobject_components/sprite_renderer.h>

namespace ns_HMGame
{
	PrefabWeapon::PrefabWeapon(ns_fretBuzz::ns_system::GameObject* a_ParentGameObject)
		: PrefabWeapon(a_ParentGameObject, "WEAPON", { 0.0f, 0.0f , 0.0f }, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, {70.0f ,70.0f })
	{
	
	}

	PrefabWeapon::PrefabWeapon(ns_fretBuzz::ns_system::GameObject* a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH)
		: ns_fretBuzz::ns_system::GameObject2D(*a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, false)
	{
		ns_fretBuzz::ns_system::ColliderData l_SensorRectColliderData;
		l_SensorRectColliderData.m_bIsSensor = true;
		l_SensorRectColliderData.m_vectColliderCategoryBits.emplace_back(ns_fretBuzz::ns_system::ColliderData::BIT_PICKUP);
		l_SensorRectColliderData.m_vectColliderMaskBits.emplace_back(ns_fretBuzz::ns_system::ColliderData::BIT_PLAYER);
		l_SensorRectColliderData.m_vectColliderMaskBits.emplace_back(ns_fretBuzz::ns_system::ColliderData::BIT_BOUNDARY);
		l_SensorRectColliderData.m_PhysicsBodyType = ns_fretBuzz::ns_system::PhysicsEngine::PHYSICS_BODY_TYPE::STATIC;
		l_SensorRectColliderData.m_ColliderShape = ns_fretBuzz::ns_system::ColliderData::SHAPE_RECT;

		ns_fretBuzz::ns_graphics::SpriteRenderer::addToGameObject(*this);
		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*this, l_SensorRectColliderData);
		ns_fretBuzz::ns_system::Behaviour::addToGameObject<Weapon>(this);
	}
}