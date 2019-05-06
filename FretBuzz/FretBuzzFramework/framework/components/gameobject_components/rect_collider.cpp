#include <fretbuzz_pch.h>
#include "system/system_defines.h"
#include "rect_collider.h"
#include "system/game_object_2d.h"
#include "system/core/input.h"
#include "system/core/resource_manager.h"
#include "graphics/shader_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		RectCollider::RectCollider(GameObject2D& a_GameObject, ColliderData& a_RectColliderData)
			: 
			Collider2D(a_GameObject, a_RectColliderData)
#ifdef _IS_DEBUG_RENDERING
			, ns_graphics::IRenderer()
#endif
		{
#ifdef _IS_DEBUG_RENDERING
			m_Material.setShader(*ns_graphics::ShaderManager::getShaderOfType(ns_graphics::Shader::DEFAULT_LINE));

			//Setup rect collider borders using LineData for debugging
			float l_fLeftX = m_ColliderData.m_v2DimensionWH.x * -0.5f;
			float l_fRightX = m_ColliderData.m_v2DimensionWH.x * 0.5f;
			float l_fTopY = m_ColliderData.m_v2DimensionWH.y * 0.5f;
			float l_fBottomY = m_ColliderData.m_v2DimensionWH.y * -0.5f;

			m_arrRectLineBorders[0] = 
				ns_graphics::LineData
					{ 
						{ l_fLeftX, l_fBottomY ,0.0f, 1.0f},
						{0.0f, 0.0f ,1.0f, 1.0f },
						{ l_fRightX, l_fBottomY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f }
					};

			m_arrRectLineBorders[1] =
				ns_graphics::LineData
					{
						{ l_fRightX, l_fBottomY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f },
						{ l_fRightX, l_fTopY, 0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f }
					};

			m_arrRectLineBorders[2] =
				ns_graphics::LineData
					{
						{ l_fRightX, l_fTopY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f },
						{ l_fLeftX, l_fTopY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f }
					};

			m_arrRectLineBorders[3] =
				ns_graphics::LineData
					{
						{ l_fLeftX, l_fTopY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f },
						{ l_fLeftX, l_fBottomY ,0.0f, 1.0f },
						{ 0.0f, 0.0f ,1.0f, 1.0f }
					};

#endif
		}

		RectCollider::~RectCollider()
		{
			
		}

		RectCollider* RectCollider::addToGameObject(GameObject2D& a_GameObject, ColliderData& a_RectColliderData)
		{
			a_RectColliderData.m_ColliderShape = ColliderData::SHAPE_RECT;
			a_RectColliderData.m_v2DimensionWH = a_GameObject.m_RectTransform.getRect().m_v2DimensionsWH;

			return IComponent::isComponentOfTypeExistInGameObj(COMPONENT_TYPE::COLLIDER_2D, &a_GameObject) ?
				nullptr : new RectCollider(a_GameObject, a_RectColliderData);
		}

		void RectCollider::update(float a_fDeltaTime)
		{
			Collider2D::Update(a_fDeltaTime);
		}

		void RectCollider::debugRender(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera)
		{
#ifdef _IS_DEBUG_RENDERING
			ns_graphics::LineBatchRenderer::submit(m_arrRectLineBorders, 4, a_mat4Transformation, m_Material);
#endif
		}
	}
}