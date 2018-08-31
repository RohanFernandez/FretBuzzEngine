#pragma once
#include "physics_engine.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{	
		PhysicsEngine* PhysicsEngine::s_pInstance = nullptr;

		PhysicsEngine::PhysicsEngine()
		{
			if (s_pInstance != nullptr)
			{
				return;
			}
			s_pInstance = this;


		}

		PhysicsEngine::~PhysicsEngine()
		{
			if (s_pInstance == this)
			{
				s_pInstance = nullptr;
			}
		}
	}
}