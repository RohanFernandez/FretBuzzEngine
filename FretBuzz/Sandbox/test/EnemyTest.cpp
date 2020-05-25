#include <fretbuzz_pch.h>
#include "EnemyTest.h"
namespace ns_HMGame
{
	EnemyTest::EnemyTest(GameObject& a_ParentGameObject, std::string a_strName)
		: ns_fretBuzz::ns_system::GameObject2D(a_ParentGameObject, a_strName, { 300.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 150.0f, 100.0f })
	{
		m_pSpriteAnimator = this->addComponent<ns_fretBuzz::ns_system::SpriteAnimationController>("Enemy");

		ns_fretBuzz::ns_system::ColliderData l_RectColliderData;
		l_RectColliderData.m_PhysicsBodyType = ns_fretBuzz::ns_system::PHYSICS_BODY_TYPE::KINEMATIC;
		l_RectColliderData.m_bIsFixedRotation = true;
		l_RectColliderData.m_v2DimensionWH = { 50.0f, 50.0f };
		m_pRectCollider = this->addComponent<ns_fretBuzz::ns_system::RectCollider>(l_RectColliderData);
	}

	//void EnemyTest::update(float a_fDeltaTime) {}

	//void EnemyTest::render(const ns_graphics::Camera& a_Camera) {}
}