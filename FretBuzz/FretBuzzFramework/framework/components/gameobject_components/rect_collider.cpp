#include <fretbuzz_pch.h>
#include "system/system_defines.h"
#include "rect_collider.h"
#include "system/game_object_2d.h"
#include <input.h>
#include <resource_manager.h>
#include "graphics/shader_manager.h"

namespace FRETBUZZ
{
		RectCollider::RectCollider(GameObject2D* a_GameObject, ColliderData& a_RectColliderData)
			: 
			Collider2D(a_GameObject, a_RectColliderData)
#ifdef _IS_DEBUG_RENDERING
			, IRenderer()
#endif
		{
			//Specialize with rect collision data
			m_ColliderData.m_ColliderShape = ColliderData::SHAPE_RECT;
			m_ColliderData.m_v2DimensionWH = m_GameObject2D.m_RectTransform.getRect().m_v2DimensionsWH;
			setupCollisionData();


#ifdef _IS_DEBUG_RENDERING
			m_Material.setShader(*ShaderManager::getShaderOfType(Shader::DEFAULT_LINE));

			//Setup rect collider borders using LineData for debugging
			float l_fLeftX = m_ColliderData.m_v2DimensionWH.x * -0.5f;
			float l_fRightX = m_ColliderData.m_v2DimensionWH.x * 0.5f;
			float l_fTopY = m_ColliderData.m_v2DimensionWH.y * 0.5f;
			float l_fBottomY = m_ColliderData.m_v2DimensionWH.y * -0.5f;

			m_arrRectLineBorders[0] = 
				LineData
					{ 
						{ l_fLeftX, l_fBottomY ,0.0f, 1.0f},
						{0.0f, 0.0f ,0.0f, 1.0f },
						{ l_fRightX, l_fBottomY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,0.0f, 1.0f }
					};

			m_arrRectLineBorders[1] =
				LineData
					{
						{ l_fRightX, l_fBottomY ,0.0f, 1.0f },
						{0.0f, 0.0f ,0.0f, 1.0f },
						{ l_fRightX, l_fTopY, 0.0f, 1.0f },
						{ 0.0f, 0.0f ,0.0f, 1.0f }
					};

			m_arrRectLineBorders[2] =
				LineData
					{
						{ l_fRightX, l_fTopY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,0.0f, 1.0f },
						{ l_fLeftX, l_fTopY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,0.0f, 1.0f }
					};

			m_arrRectLineBorders[3] =
				LineData
					{
						{ l_fLeftX, l_fTopY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,0.0f, 1.0f },
						{ l_fLeftX, l_fBottomY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,0.0f, 1.0f }
					};

#endif
		}

		RectCollider::~RectCollider()
		{
			
		}

		void RectCollider::lateUpdate(const float& a_fDeltaTime)
		{
			Collider2D::lateUpdate(a_fDeltaTime);
		}

		void RectCollider::debugRender(const glm::mat4& a_mat4Transformation, const Camera& a_Camera)
		{
#ifdef _IS_DEBUG_RENDERING
			LineBatchRenderer::submit(m_arrRectLineBorders, 4, a_mat4Transformation, m_Material);
#endif
		}
}