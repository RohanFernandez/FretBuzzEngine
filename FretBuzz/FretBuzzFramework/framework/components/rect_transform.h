#pragma once
#include "transform.h"
#include "graphics/rect.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class RectTransform : public Transform
		{
		friend class GameObject2D;
		protected:
			ns_graphics::Rect m_Rect;

		public:

			RectTransform(glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH, Transform* a_pParentTransform)
				: Transform(a_v3Position, a_v3Rotation, a_v3Scale, a_pParentTransform),
				m_Rect{ a_v2DimensionWH }
			{
				
			}

			virtual ~RectTransform() {};

			void setDimensionWH(glm::vec2 a_v2DimensionWH)
			{
				m_Rect.reset(a_v2DimensionWH);
			}

			const ns_graphics::Rect& getRect() const
			{
				return m_Rect;
			}
		};
	}
}