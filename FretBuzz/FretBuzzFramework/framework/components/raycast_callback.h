#pragma once
#include <Box2D/Box2D.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Collider2D;
		class RaycastCallback : public b2RayCastCallback
		{
		private:
			b2Fixture* m_pIntersectedFixture = nullptr;

		public:
			void reset();
			virtual float32 ReportFixture(b2Fixture* a_pFixture, const b2Vec2& a_v2Point, const b2Vec2& a_v2Normal, float32 a_fFraction) override;
			Collider2D* getIntersectedCollider2D() const;
		};
	}
}