#pragma once
#include "image.h"
#include "../../system/game_object_2d.h"
#include "../../graphics/sprite_batch_renderer.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Image::Image(ns_system::GameObject2D& a_GameObject2D, Sprite* a_pSprite, bool a_bIsEnabled)
			: ns_system::IComponent2D(ns_system::COMPONENT_TYPE::IMAGE, a_GameObject2D, a_bIsEnabled),
			m_v2Dimensions(m_GameObject2D.m_RectTransform.m_v2DimensionWH),
		    m_pSprite{a_pSprite}
		{

		}

		Image::~Image()
		{
		
		}

		Image* Image::addToGameObject(ns_system::GameObject2D& a_GameObject2D, Sprite* a_pSprite, bool a_bIsEnabled)
		{
			return IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::IMAGE, &a_GameObject2D) ?
				nullptr : new Image(a_GameObject2D, a_pSprite, a_bIsEnabled);
		}

		void Image::setSprite(Sprite* a_pSpite)
		{
			m_pSprite = a_pSpite;
		}

		void Image::render(const glm::mat4& a_mat4Transformation, const ns_system::Camera& a_Camera)
		{
			if (getIsEnabled() || m_pSprite == nullptr)
			{
				return;
			}

			//SpriteBatchRenderer::submit()
		}
	}
}