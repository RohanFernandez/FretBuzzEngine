#pragma once
#include "transform.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class RectTransform : public Transform
		{
		friend class GameObject2D;
		protected:

		public:

			RectTransform(glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH, Transform* a_pParentTransform)
				: Transform(a_v3Position, a_v3Rotation, a_v3Scale, a_pParentTransform),
				m_v2DimensionWH{ a_v2DimensionWH }
			{
				
			}

			virtual ~RectTransform() {};
			glm::vec2 m_v2DimensionWH;

			void setDimensionWH(glm::vec2 a_v2DimensionWH)
			{
				m_v2DimensionWH = a_v2DimensionWH;
			}

			const glm::vec2 getDimensionWH() const
			{
				return m_v2DimensionWH;
			}
		};
	}
}