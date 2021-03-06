#include <fretbuzz_pch.h>
#include "prefab_weapon.h"
#include <game/managers/weapon/weapon.h>
#include <components/gameobject_components/sprite_renderer.h>

namespace ns_HMGame
{
	PrefabWeapon::PrefabWeapon(FRETBUZZ::GameObject* a_ParentGameObject)
		: PrefabWeapon(a_ParentGameObject, "WEAPON", { 0.0f, 0.0f , 0.0f }, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, {70.0f ,70.0f })
	{
	
	}

	PrefabWeapon::PrefabWeapon(FRETBUZZ::GameObject* a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH)
		: FRETBUZZ::GameObject2D(*a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, "PICKUP", false)
	{
		FRETBUZZ::ColliderData l_SensorRectColliderData;
		
		l_SensorRectColliderData.m_CategoryMask.addLayers(std::vector<std::string>{"PICKUP"});
		l_SensorRectColliderData.m_CollisionMask.addLayers(std::vector<std::string>{"PLAYER", "BOUNDARY"});

		l_SensorRectColliderData.m_ColliderShape = FRETBUZZ::ColliderData::SHAPE_RECT;
		l_SensorRectColliderData.m_bIsSensor = false;
		l_SensorRectColliderData.m_bIsBullet = false;
		l_SensorRectColliderData.m_fDensity = 1.0f;
		l_SensorRectColliderData.m_fLinearDamping = 0.5f;
		l_SensorRectColliderData.m_fAngularDamping = 0.5f;

		this->addComponent<FRETBUZZ::SpriteRenderer>();
		this->addComponent<FRETBUZZ::RectCollider>(l_SensorRectColliderData);
		this->addComponent<Weapon>();
	}
}