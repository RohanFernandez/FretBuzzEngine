#include <fretbuzz_pch.h>
#include "EnemyTest.h"
namespace ns_HMGame
{
	EnemyTest::EnemyTest(GameObject& a_ParentGameObject, std::string a_strName)
		: FRETBUZZ::GameObject2D(a_ParentGameObject, a_strName, { 300.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 150.0f, 100.0f })
	{
		m_pSpriteAnimator = this->addComponent<FRETBUZZ::SpriteAnimationController>("Enemy");

		FRETBUZZ::ColliderData l_RectColliderData;
		l_RectColliderData.m_PhysicsBodyType = FRETBUZZ::PHYSICS_BODY_TYPE::KINEMATIC;
		l_RectColliderData.m_bIsFixedRotation = true;
		l_RectColliderData.m_v2DimensionWH = { 50.0f, 50.0f };
		m_pRectCollider = this->addComponent<FRETBUZZ::RectCollider>(l_RectColliderData);
	}

	//void EnemyTest::update(float a_fDeltaTime) {}

	//void EnemyTest::render(const Camera& a_Camera) {}
}