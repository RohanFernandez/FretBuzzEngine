#include <fretbuzz_pch.h>
#include "prefab_enemy.h"
#include "game/managers/enemy/EnemyController.h"

namespace ns_HMGame
{
	PrefabEnemy::PrefabEnemy(FRETBUZZ::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH)
		: FRETBUZZ::GameObject2D(a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, "ENEMY", true)
	{
		FRETBUZZ::GameObject2D* l_pEnemyUpperGameObj = FRETBUZZ::GameObject2D::instantiate(*this, "EnemyUpper", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, "ENEMY");
		FRETBUZZ::GameObject2D* l_pEnemyLowerGameObj = FRETBUZZ::GameObject2D::instantiate(*this, "EnemyLegs", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f }, "ENEMY");

		l_pEnemyLowerGameObj->addComponent<FRETBUZZ::SpriteAnimationController>("EnemyLegs");
		l_pEnemyUpperGameObj->addComponent<FRETBUZZ::SpriteAnimationController>("Enemy");

		FRETBUZZ::ColliderData l_RectColliderData;
		l_RectColliderData.m_PhysicsBodyType = FRETBUZZ::PHYSICS_BODY_TYPE::DYNAMIC;

		l_RectColliderData.m_CategoryMask.addLayers(std::vector<std::string>{"ENEMY"});
		l_RectColliderData.m_CollisionMask.addLayers(std::vector<std::string>{"PLAYER", "BOUNDARY", "BULLET"});

		this->addComponent<FRETBUZZ::RectCollider>(l_RectColliderData);
		this->addComponent<EnemyController>(l_pEnemyUpperGameObj, l_pEnemyLowerGameObj);
	}
}