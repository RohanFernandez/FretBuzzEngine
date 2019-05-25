#include <fretbuzz_pch.h>
#include "prefab_enemy.h"
#include "game/managers/enemy/EnemyController.h"

namespace ns_HMGame
{
	PrefabEnemy::PrefabEnemy(ns_fretBuzz::ns_system::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH)
		: ns_fretBuzz::ns_system::GameObject2D(a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, true)
	{
		ns_fretBuzz::ns_system::GameObject2D* l_pEnemyUpperGameObj = ns_fretBuzz::ns_system::GameObject2D::instantiate(*this, "EnemyUpper", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, true);
		ns_fretBuzz::ns_system::GameObject2D* l_pEnemyLowerGameObj = ns_fretBuzz::ns_system::GameObject2D::instantiate(*this, "EnemyLegs", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, true);

		ns_fretBuzz::ns_system::SpriteAnimationController::addToGameObject(*l_pEnemyLowerGameObj, "EnemyLegs");
		ns_fretBuzz::ns_system::SpriteAnimationController::addToGameObject(*l_pEnemyUpperGameObj, "Enemy");

		ns_fretBuzz::ns_system::ColliderData l_RectColliderData;
		l_RectColliderData.m_PhysicsBodyType = ns_fretBuzz::ns_system::PHYSICS_BODY_TYPE::DYNAMIC;
		l_RectColliderData.m_usetColliderMaskBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_BOUNDARY);
		l_RectColliderData.m_usetColliderMaskBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_PICKUP);
		l_RectColliderData.m_usetColliderMaskBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_BULLET);

		l_RectColliderData.m_usetColliderCategoryBits.insert(ns_fretBuzz::ns_system::ColliderData::BIT_ENEMY);

		ns_fretBuzz::ns_system::RectCollider::addToGameObject(*this, l_RectColliderData);
		ns_fretBuzz::ns_system::Behaviour::addToGameObject<EnemyController>(this, l_pEnemyUpperGameObj, l_pEnemyLowerGameObj);
	}
}