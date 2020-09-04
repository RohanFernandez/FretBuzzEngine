#include <fretbuzz_pch.h>
#include "raycast_callback.h"

namespace FRETBUZZ
{
	void RaycastCallback::reset()
	{
		m_pIntersectedFixture = nullptr;
	}

	float RaycastCallback::ReportFixture(b2Fixture* a_pFixture, const b2Vec2& a_v2Point, const b2Vec2& a_v2Normal, float a_fFraction)
	{
		m_pIntersectedFixture = a_pFixture;
		return a_fFraction;
	}

	Collider2D* RaycastCallback::getIntersectedCollider2D() const
	{
		if (m_pIntersectedFixture != nullptr)
		{
			return  static_cast<Collider2D*>(m_pIntersectedFixture->GetBody()->GetUserData());
		}
		return nullptr;
	}
}