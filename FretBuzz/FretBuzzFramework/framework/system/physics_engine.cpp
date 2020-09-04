#include <fretbuzz_pch.h>
#include <components/raycast_callback.h>
#include <components/collider_2d.h>
#include "physics_engine.h"
#include "system.h"

namespace FRETBUZZ
{
	PhysicsEngine* PhysicsEngine::s_pInstance = nullptr;

	PhysicsEngine::PhysicsEngine(b2Vec2 a_v2Gravity, int a_iVelocityIteration, int a_iStepIteration)
		: m_iVelocityIteration{ a_iVelocityIteration },
			m_iStepIteration{ a_iStepIteration },
		m_stackContactEvent()
	{
		s_pInstance = this;
		m_pB2World = new b2World(a_v2Gravity);
		m_pB2World->SetAutoClearForces(true);
	}

	PhysicsEngine::~PhysicsEngine()
	{
		delete m_pB2World;
		m_pB2World = nullptr;
	}

	PhysicsEngine* PhysicsEngine::initialize(b2Vec2 a_v2Gravity, int a_iVelocityIteration, int a_iStepIteration)
	{
		if (s_pInstance != nullptr)
		{
			std::cout << "PhysicsEngine::initialize:: PhysicsEngine already exists.\n";
			return nullptr;
		}

		s_pInstance = new PhysicsEngine(a_v2Gravity, a_iVelocityIteration, a_iStepIteration);
		return s_pInstance;
	}

	void PhysicsEngine::destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	const PhysicsEngine* PhysicsEngine::get()
	{
		return s_pInstance;
	}

	// Contacts i.e. TriggerEnter, TriggerExit, CollisionEnter, CollisionExit that occured during step
	// are collected and invoked after the step because Box2D is locked during and no Box2D component should be calculated during.
	void PhysicsEngine::step(const float& a_fDeltaTime)
	{
		m_pB2World->Step(a_fDeltaTime, m_iVelocityIteration, m_iStepIteration);
		invokeContactCallbacks();
	}

	void PhysicsEngine::invokeContactCallbacks()
	{
		Collider2DContactEvent l_ContactEvent;
		while (!m_stackContactEvent.empty())
		{
			l_ContactEvent = m_stackContactEvent.top();
			l_ContactEvent.invoke();
			m_stackContactEvent.pop();
		}
	}

	b2World* PhysicsEngine::getB2World()
	{
		return s_pInstance->m_pB2World;
	}

	void PhysicsEngine::Raycast(Collider2D*& a_pCollider2D, glm::vec2 a_v2Point1, glm::vec2 a_v2Point2)
	{
		s_pInstance->m_RaycastCallback.reset();
		s_pInstance->m_pB2World->RayCast(&s_pInstance->m_RaycastCallback, b2Vec2{ a_v2Point1.x, a_v2Point1.y }, b2Vec2{ a_v2Point2.x, a_v2Point2.y });
		a_pCollider2D = s_pInstance->m_RaycastCallback.getIntersectedCollider2D();
	}

	void PhysicsEngine::AddContactEvent(Collider2DContactEvent a_ContactEvent)
	{
		s_pInstance->m_stackContactEvent.push(a_ContactEvent);
	}
}