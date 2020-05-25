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

			PHYSICS_BODY_TYPE m_PhysicsBodyType = PHYSICS_BODY_TYPE::STATIC;
			bool m_bIsSensor = false;
			bool m_bIsBullet = false;
			bool m_bIsFixedRotation = true;
			float m_fDensity = 1.0f;
			float m_fFriction = 0.0f;
			float m_fLinearDamping = 0.0f;
			float m_fAngularDamping = 0.0f;
			COLLIDER_SHAPE m_ColliderShape = SHAPE_RECT;
			glm::vec2 m_v2DimensionWH = { 0, 0 };
			glm::vec2 m_v2RelativePos = { 0, 0 };
			float m_fRadius = 1.0f;
			int m_iGroupIndex = 0;
			LayerMask m_CategoryMask;
			LayerMask m_CollisionMask;

			ColliderData(){}

			ColliderData(ColliderData& a_ColliderData)
			{
				*this = a_ColliderData;
			}

			void operator=(ColliderData& a_Other)
			{
				m_PhysicsBodyType		    = a_Other.m_PhysicsBodyType;
				m_bIsSensor				    = a_Other.m_bIsSensor;
				m_bIsBullet				    = a_Other.m_bIsBullet;
				m_bIsFixedRotation		    = a_Other.m_bIsFixedRotation;
				m_fLinearDamping			= a_Other.m_fLinearDamping;
				m_fAngularDamping			= a_Other.m_fAngularDamping;
				m_fDensity					= a_Other.m_fDensity;
				m_fFriction					= a_Other.m_fFriction;
				m_ColliderShape			    = a_Other.m_ColliderShape;
				m_v2RelativePos			    = a_Other.m_v2RelativePos;
				m_fRadius				    = a_Other.m_fRadius;
				m_v2DimensionWH			    = a_Other.m_v2DimensionWH;
				m_iGroupIndex			    = a_Other.m_iGroupIndex;
				m_CollisionMask				= a_Other.m_CollisionMask;
				m_CategoryMask		= a_Other.m_CategoryMask;
			}
		};
	}
}