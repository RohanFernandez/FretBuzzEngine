#include <fretbuzz_pch.h>
#include <components/raycast_callback.h>
#include <components/collider_2d.h>
#include "physics_engine.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{	
		PhysicsEngine* PhysicsEngine::s_pInstance = nullptr;

		PhysicsEngine::PhysicsEngine(b2Vec2 a_v2Gravity, int a_iVelocityIteration, int a_iStepIteration)
			: m_iVelocityIteration{ a_iVelocityIteration },
			  m_iStepIteration{ a_iStepIteration }
		{
			s_pInstance = this;
			m_pB2World = new b2World(a_v2Gravity);
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

		void PhysicsEngine::update(float a_fDeltaTime)
		{
			m_pB2World->Step(a_fDeltaTime, m_iVelocityIteration, m_iStepIteration);
		}

		b2World* PhysicsEngine::getB2World()
		{
			return s_pInstance->m_pB2World;
		}

		void PhysicsEngine::Raycast(Collider2D*& a_pCollider2D, glm::vec2& a_v2Point1, glm::vec2& a_v2Point2)
		{
			s_pInstance->m_RaycastCallback.reset();
			s_pInstance->m_pB2World->RayCast(&s_pInstance->m_RaycastCallback, b2Vec2{ a_v2Point1.x, a_v2Point1.y }, b2Vec2{ a_v2Point2.x, a_v2Point2.y });
			a_pCollider2D = s_pInstance->m_RaycastCallback.getIntersectedCollider2D();
		}
	}
}