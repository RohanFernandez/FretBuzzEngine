#pragma once
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
			if (s_pInstance != nullptr)
			{
				return;
			}
			s_pInstance = this;

			m_pB2World = new b2World(a_v2Gravity);
		}

		PhysicsEngine::~PhysicsEngine()
		{
			if (s_pInstance == this)
			{
				delete m_pB2World;
				m_pB2World = nullptr;

				s_pInstance = nullptr;
			}
		}

		void PhysicsEngine::update(float a_fDeltaTime)
		{
			m_pB2World->Step(a_fDeltaTime, m_iVelocityIteration, m_iStepIteration);
		}

		b2World* PhysicsEngine::getB2World()
		{
			return s_pInstance->m_pB2World;
		}
	}
}