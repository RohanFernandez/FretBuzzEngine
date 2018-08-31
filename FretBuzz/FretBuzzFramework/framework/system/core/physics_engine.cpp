#pragma once
#include "physics_engine.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{	
		PhysicsEngine* PhysicsEngine::s_pInstance = nullptr;

		PhysicsEngine::PhysicsEngine(b2Vec2 a_v2Gravity)
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
	}
}