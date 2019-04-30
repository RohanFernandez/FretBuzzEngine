#pragma once
#include <system/core/physics_engine.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		struct ColliderData
		{
			enum COLLIDER_SHAPE
			{
				SHAPE_RECT,
				SHAPE_CIRCLE
			};

			PhysicsEngine::PHYSICS_BODY_TYPE m_PhysicsBodyType = PhysicsEngine::PHYSICS_BODY_TYPE::STATIC;
			bool m_bIsSensor = false;
			bool m_bIsBullet = false;
			bool m_bIsFixedRotation = true;
			COLLIDER_SHAPE m_ColliderShape = SHAPE_RECT;
			glm::vec2 m_v2DimensionWH = { 0, 0 };
			glm::vec2 m_v2RelativePos = { 0, 0 };
			float m_fRadius = 1.0f;

			void operator=(ColliderData& a_Other)
			{
				m_PhysicsBodyType = a_Other.m_PhysicsBodyType;
				m_bIsSensor = a_Other.m_bIsSensor;
				m_bIsBullet = a_Other.m_bIsBullet;
				m_bIsFixedRotation = a_Other.m_bIsFixedRotation;
				m_ColliderShape = a_Other.m_ColliderShape;
				m_v2RelativePos = a_Other.m_v2RelativePos;
				m_fRadius = a_Other.m_fRadius;
			}
		};
	}
}