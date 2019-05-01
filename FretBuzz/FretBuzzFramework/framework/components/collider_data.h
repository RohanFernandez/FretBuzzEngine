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

			enum COLLIDER_BITS
			{
				BIT_NOTHING		= 0x0000,
				BIT_PLAYER		= 0x0001,
				BIT_ENEMY		= 0x0002,
				BIT_PICKUP		= 0x0004,
				BIT_BOUNDARY	= 0x0008,
				BIT_EVERYTHING  = 0x8888
			};

			PhysicsEngine::PHYSICS_BODY_TYPE m_PhysicsBodyType = PhysicsEngine::PHYSICS_BODY_TYPE::STATIC;
			bool m_bIsSensor = false;
			bool m_bIsBullet = false;
			bool m_bIsFixedRotation = true;
			COLLIDER_SHAPE m_ColliderShape = SHAPE_RECT;
			glm::vec2 m_v2DimensionWH = { 0, 0 };
			glm::vec2 m_v2RelativePos = { 0, 0 };
			float m_fRadius = 1.0f;
			int m_iGroupIndex = 0;
			std::vector<uint16> m_vectColliderCategoryBits;
			std::vector<uint16> m_vectColliderMaskBits;

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
				m_ColliderShape			    = a_Other.m_ColliderShape;
				m_v2RelativePos			    = a_Other.m_v2RelativePos;
				m_fRadius				    = a_Other.m_fRadius;
				m_v2DimensionWH			    = a_Other.m_v2DimensionWH;
				m_iGroupIndex			    = a_Other.m_iGroupIndex;
				m_vectColliderMaskBits		= a_Other.m_vectColliderMaskBits;
				m_vectColliderCategoryBits  = a_Other.m_vectColliderCategoryBits;
			}
		};
	}
}