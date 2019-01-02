#pragma once
#include "image.h"
#include "system/game_object_2d.h"
#include "graphics/sprite_batch_renderer.h"
#include "system/core/resource_manager.h"
#include "graphics/shader_manager.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		const std::vector<glm::vec2> Image::s_vectTexcoords = 
		{
			{ 0.0f, 0.0f },  //0
			{ 0.0f, 1.0f },  //1
			{ 1.0f, 1.0f },  //2
			{ 1.0f, 0.0f }   //3
		};

		Image::Image(ns_system::GameObject2D& a_GameObject2D, Sprite* a_pSprite, glm::vec4 a_v4Color, bool a_bIsEnabled)
			: ns_system::IComponent2D(ns_system::COMPONENT_TYPE::IMAGE, a_GameObject2D, a_bIsEnabled),
			m_pSprite{ a_pSprite },
			m_Color{a_v4Color}
		{
			m_Material.setShader(*ShaderManager::getShaderOfType(Shader::DEFAULT_SPRITE));
		}

		Image::~Image()
		{

		}

		Image* Image::addToGameObject(ns_system::GameObject2D& a_GameObject2D, Sprite* a_pSprite, glm::vec4 a_v4Color, bool a_bIsEnabled)
		{
			return IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::IMAGE, &a_GameObject2D) ?
				nullptr : new Image(a_GameObject2D, a_pSprite, a_v4Color, a_bIsEnabled);
		}

		void Image::setSprite(Sprite* a_pSpite)
		{
			m_pSprite = a_pSpite;
		}

		void Image::render(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera)
		{
			if (((m_pSprite == nullptr) &&
				(m_Color.w == 0.0f)))
			{
				return;
			}

			const Texture* l_pTexture = (m_pSprite == nullptr) ? nullptr : m_pSprite->getTexture();
			SpriteBatchRenderer::submit(m_GameObject2D.m_RectTransform.getRect().m_VertPosition, m_Color, l_pTexture, s_vectTexcoords, a_mat4Transformation, m_Material);
		}

		void Image::setColor(glm::vec4 a_Color)
		{
			m_Color = a_Color;
		}

		const glm::vec4& Image::getColor(glm::vec4 a_Color) const
		{
			return m_Color;
		}

		void Image::setShader(Shader* a_pShader)
		{
			m_pShader = a_pShader;
		}
	}
}