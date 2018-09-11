#pragma once
#include "sprite_renderer.h"
#include "../viewport.h"
#include <iostream>
#include "../../system/game_object.h"
#include "../../system/core/resource_manager.h"
#include "../../graphics/sprite_batch_renderer.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		SpriteRenderer::SpriteRenderer(ns_system::GameObject& a_GameObj, Sprite* a_Sprite, Shader* a_pShader)
			: ns_system::IComponent(ns_system::COMPONENT_TYPE::SPRITE_RENDERER, a_GameObj),
			m_pSprite{ a_Sprite },
			m_pShader{ a_pShader },
			m_DefaltSprite()
		{
			initialize();
		}

		SpriteRenderer::SpriteRenderer(ns_system::GameObject& a_GameObj)
			: SpriteRenderer(a_GameObj, nullptr, nullptr)
		{
			initialize();
		}

		SpriteRenderer::SpriteRenderer(ns_system::GameObject& a_GameObj, std::string a_strSpriteID)
			: SpriteRenderer(a_GameObj,ns_system::ResourceManager::getResource<SpriteGroup>(a_strSpriteID)->getSprite(0), nullptr)
		{
			initialize();
		}

		SpriteRenderer::SpriteRenderer(ns_system::GameObject& a_GameObj, glm::vec4 a_v4Color, glm::vec2 a_v2Dimensions)
			: ns_system::IComponent(ns_system::COMPONENT_TYPE::SPRITE_RENDERER, a_GameObj),
			m_DefaltSprite(a_v2Dimensions, a_v4Color)
		{
			initialize();
		}

		SpriteRenderer::~SpriteRenderer()
		{
			m_pSprite = nullptr;
			m_pShader = nullptr;
		}

		SpriteRenderer* SpriteRenderer::addToGameObject(ns_system::GameObject& a_GameObj)
		{
			return IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::SPRITE_RENDERER, &a_GameObj) ?
				nullptr : new SpriteRenderer(a_GameObj);
		}

		SpriteRenderer* SpriteRenderer::addToGameObject(ns_system::GameObject& a_GameObj, Sprite* a_Sprite, Shader* a_pShader)
		{
			return IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::SPRITE_RENDERER, &a_GameObj) ?
				nullptr : new SpriteRenderer(a_GameObj, a_Sprite, a_pShader);
		}

		SpriteRenderer* SpriteRenderer::addToGameObject(ns_system::GameObject& a_GameObj, std::string a_strSpriteID)
		{
			return IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::SPRITE_RENDERER, &a_GameObj) ?
				nullptr : new SpriteRenderer(a_GameObj, a_strSpriteID);
		}

		SpriteRenderer* SpriteRenderer::addToGameObject(ns_system::GameObject& a_GameObj, glm::vec4 a_v4Color, glm::vec2 a_v2Dimensions)
		{
			return IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::SPRITE_RENDERER, &a_GameObj) ?
				nullptr : new SpriteRenderer(a_GameObj, a_v4Color, a_v2Dimensions);
		}

		void SpriteRenderer::setShader(std::string a_strShaderId)
		{
			Shader* l_pShader = ns_system::ResourceManager::getResource<Shader>(a_strShaderId);
			m_pShader = (l_pShader == nullptr) ? ns_system::ResourceManager::getResource<Shader>(Shader::DEFAULT_SHADER_ID) : l_pShader;
		}

		void SpriteRenderer::setShader(Shader* a_pShader)
		{
			m_pShader = (a_pShader == nullptr) ? ns_system::ResourceManager::getResource<Shader>(Shader::DEFAULT_SHADER_ID) : a_pShader;
		}

		void SpriteRenderer::initialize()
		{
			setShader(m_pShader);
		}

		void SpriteRenderer::setSprite(Sprite* a_Sprite)
		{
			m_pSprite = a_Sprite;
		}

		void SpriteRenderer::setSprite(std::string a_strSpriteID)
		{
			m_pSprite = ns_system::ResourceManager::getResource<SpriteGroup>(a_strSpriteID)->getSprite(0);
			setSprite(m_pSprite);
		}

		void SpriteRenderer::render(const glm::mat4& a_mat4Transformation, const ns_system::Viewport& a_Camera)
		{
			Sprite* l_pSpriteToRender = ((m_pSprite == nullptr) ? &m_DefaltSprite : m_pSprite);
			SpriteBatchRenderer::submit(*l_pSpriteToRender, a_mat4Transformation, m_pShader);

			/*const Shader& l_CurrentShader = *(l_CurrentSprite.getShader());
			l_CurrentShader.bind();

			l_CurrentShader.setUniforMat4fv(Sprite::UNIFORM_PROJECTION_MATRIX, a_Camera.getProjectionMatrix());
			l_CurrentShader.setUniforMat4fv(Sprite::UNIFORM_VIEW_MATRIX, a_Camera.getViewMatrix());
			l_CurrentShader.setUniforMat4fv(Sprite::UNIFORM_MODEL_MATRIX, a_mat4Transformation);

			glActiveTexture(GL_TEXTURE0);
			l_CurrentSprite.getTexture()->bind();

			l_CurrentShader.setUniform1i(Sprite::UNIFORM_TEXTURE_SAMPLER, 0);

			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);*/
		}
	}
}