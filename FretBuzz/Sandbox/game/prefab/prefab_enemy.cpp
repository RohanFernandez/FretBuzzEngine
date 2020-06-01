#include <fretbuzz_pch.h>
#include "prefab_enemy.h"
#include "game/managers/enemy/EnemyController.h"

namespace ns_HMGame
{
	PrefabEnemy::PrefabEnemy(ns_fretBuzz::ns_system::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH)
		: ns_fretBuzz::ns_system::GameObject2D(a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, "ENEMY", true)
	{
		ns_fretBuzz::ns_system::GameObject2D* l_pEnemyUpperGameObj = ns_fretBuzz::ns_system::GameObject2D::instantiate(*this, "EnemyUpper", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, "ENEMY");
		ns_fretBuzz::ns_system::GameObject2D* l_pEnemyLowerGameObj = ns_fretBuzz::ns_system::GameObject2D::instantiate(*this, "EnemyLegs", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, "ENEMY");

		l_pEnemyLowerGameObj->addComponent<ns_fretBuzz::ns_system::SpriteAnimationController>("EnemyLegs");
		l_pEnemyUpperGameObj->addComponent<ns_fretBuzz::ns_system::SpriteAnimationController>("Enemy");

		ns_fretBuzz::ns_system::ColliderData l_RectColliderData;
		l_RectColliderData.m_PhysicsBodyType = ns_fretBuzz::ns_system::PHYSICS_BODY_TYPE::DYNAMIC;

		l_RectColliderData.m_CategoryMask.addLayers(std::vector<std::string>{"ENEMY"});
		l_RectColliderData.m_CollisionMask.addLayers(std::vector<std::string>{"PLAYER", "BOUNDARY", "BULLET"});

		this->addComponent<ns_fretBuzz::ns_system::RectCollider>(l_RectColliderData);
		this->addComponent<EnemyController>(l_pEnemyUpperGameObj, l_pEnemyLowerGameObj);
	}
}