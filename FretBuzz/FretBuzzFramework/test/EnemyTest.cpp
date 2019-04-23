#include <fretbuzz_pch.h>
#include "EnemyTest.h"
namespace ns_fretBuzz
{
	EnemyTest::EnemyTest(GameObject& a_ParentGameObject, std::string a_strName)
		: ns_system::GameObject2D(a_ParentGameObject, a_strName, { 300.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 150.0f, 100.0f }, true)
	{
		m_pSpriteAnimator = ns_system::SpriteAnimationController::addToGameObject(*this, "Enemy");
		m_pRectCollider = ns_system::RectCollider::addToGameObject(*this, { 50.0f, 50.0f }, ns_system::PhysicsEngine::PHYSICS_BODY_TYPE::KINEMATIC, true);
	}

	//void EnemyTest::update(float a_fDeltaTime) {}

	//void EnemyTest::render(const ns_graphics::Camera& a_Camera) {}
}