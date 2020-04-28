#include <fretbuzz_pch.h>
#include "prefab_bullet.h"
#include "game/managers/bullet/bullet.h"
#include <components/gameobject_components/rect_collider.h>
#include <components/gameobject_components/sprite_renderer.h>

namespace ns_HMGame
{
	PrefabBullet::PrefabBullet(ns_fretBuzz::ns_system::GameObject* a_ParentGameObject)
		: PrefabBullet(a_ParentGameObject, "BULLET", { 0.0f, 0.0f , 0.0f }, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 10.0f ,10.0f})
	{

	}
	
	PrefabBullet::PrefabBullet(ns_fretBuzz::ns_system::GameObject* a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH)
		: ns_fretBuzz::ns_system::GameObject2D(*a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, ns_fretBuzz::ns_system::Layer(), false)
	{
		ns_fretBuzz::ns_system::ColliderData l_SensorRectColliderData;
		l_SensorRectColliderData.m_usetColliderCategoryBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_BULLET);
		l_SensorRectColliderData.m_usetColliderMaskBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_PLAYER);
		l_SensorRectColliderData.m_usetColliderMaskBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_ENEMY);
		l_SensorRectColliderData.m_usetColliderMaskBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_BOUNDARY);
		l_SensorRectColliderData.m_PhysicsBodyType = ns_fretBuzz::ns_system::PHYSICS_BODY_TYPE::DYNAMIC;
		l_SensorRectColliderData.m_ColliderShape = ns_fretBuzz::ns_system::ColliderData::SHAPE_RECT;
		l_SensorRectColliderData.m_bIsSensor = true;
		l_SensorRectColliderData.m_bIsBullet = false;
		l_SensorRectColliderData.m_fDensity = 0.0f;

		this->addComponent<ns_fretBuzz::ns_system::RectCollider>(l_SensorRectColliderData);
		this->addComponent<ns_fretBuzz::ns_graphics::SpriteRenderer>();
		this->addComponent<Bullet>();
	}
}