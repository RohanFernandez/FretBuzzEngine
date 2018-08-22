#pragma once
#include "sprite_renderer.h"
#include "../camera/camera.h"
#include <iostream>
#include "../../game/game_object.h"
#include "../../system/resource_manager.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		SpriteRenderer::SpriteRenderer(ns_system::GameObject& a_GameObj)
			: ns_system::IComponent(s_COMPONENT_TYPE, a_GameObj),
			m_pSprite{ nullptr}
		{
			initialize();
		}

		SpriteRenderer::SpriteRenderer(ns_system::GameObject& a_GameObj, Sprite* a_Sprite)
			: ns_system::IComponent(s_COMPONENT_TYPE, a_GameObj),
			m_pSprite{ a_Sprite }
		{
			initialize();
		}

		SpriteRenderer::SpriteRenderer(ns_system::GameObject& a_GameObj, std::string a_strSpriteID)
			: ns_system::IComponent(s_COMPONENT_TYPE, a_GameObj),
			m_pSprite {ns_system::ResourceManager::getResource<SpriteSheet>(a_strSpriteID)->getSprite(0)}
		{
			initialize();
		}

		SpriteRenderer::~SpriteRenderer()
		{
			m_pSprite = nullptr;
		}

		SpriteRenderer* SpriteRenderer::addToGameObject(ns_system::GameObject& a_GameObj)
		{
			if (!a_GameObj.isComponentTypeExist(s_COMPONENT_TYPE))
			{
				return new SpriteRenderer(a_GameObj);
			}
			std::cout << "SpriteRenderer::addToGameObject:: Component of Sprite Renderer already included in the GameObject ::'" << a_GameObj.getName() << "' \n";
			return nullptr;
		}

		SpriteRenderer* SpriteRenderer::addToGameObject(ns_system::GameObject& a_GameObj, Sprite* a_Sprite)
		{
			if (!a_GameObj.isComponentTypeExist(s_COMPONENT_TYPE))
			{
				return new SpriteRenderer(a_GameObj, a_Sprite);
			}
			std::cout << "SpriteRenderer::addToGameObject:: Component of Sprite Renderer already included in the GameObject ::'" << a_GameObj.getName() << "' \n";
			return nullptr;
		}

		void SpriteRenderer::initialize()
		{
			for (int l_iAttribIndex = 0; l_iAttribIndex < Sprite::s_VERT_COUNT; l_iAttribIndex++)
			{
				m_SpriteAttributes[l_iAttribIndex].m_v3Position = Sprite::s_VERTICES[l_iAttribIndex];
			}

			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_IBO);

			glBindVertexArray(m_VAO);

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, Sprite::s_VERT_COUNT * sizeof(SpriteAttributes), m_SpriteAttributes, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteAttributes), (const void*)offsetof(SpriteAttributes, SpriteAttributes::m_v3Position));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteAttributes), (const void*)offsetof(SpriteAttributes, SpriteAttributes::m_v2TexCoords));
			glEnableVertexAttribArray(1);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Sprite::s_INDICES), Sprite::s_INDICES, GL_STATIC_DRAW);

			glBindVertexArray(0);
		}

		void SpriteRenderer::setSprite(Sprite* a_Sprite)
		{
			m_pSprite = a_Sprite;
			if (m_pSprite == nullptr){return;}

			const std::vector<glm::vec2>& l_vectTexCoords = m_pSprite->getTexCoords();

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			SpriteAttributes* l_pVertexData = (SpriteAttributes*)(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

			for (int l_iSpriteAttribIndex = 0; l_iSpriteAttribIndex < Sprite::s_VERT_COUNT; l_iSpriteAttribIndex++, l_pVertexData++)
			{
				l_pVertexData->m_v2TexCoords = l_vectTexCoords[l_iSpriteAttribIndex];
			}
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			l_pVertexData = nullptr;
		}

		void SpriteRenderer::setSprite(std::string a_strSpriteID)
		{
			m_pSprite = ns_system::ResourceManager::getResource<SpriteSheet>(a_strSpriteID)->getSprite(0);
			if (m_pSprite == nullptr){return;}

			setSprite(m_pSprite);
		}

		void SpriteRenderer::render(const ns_system::Camera& a_Camera)
		{
			if (!m_bIsAllowedToRender || (m_pSprite == nullptr)) { return; }
			Sprite& l_CurrentSprite = *m_pSprite;

			const Shader& l_CurrentShader = *(l_CurrentSprite.getShader());
			l_CurrentShader.bind();

			l_CurrentShader.setUniforMat4fv(Sprite::UNIFORM_PROJECTION_MATRIX, a_Camera.getProjectionMatrix());
			l_CurrentShader.setUniforMat4fv(Sprite::UNIFORM_VIEW_MATRIX, a_Camera.getViewMatrix());

			ns_system::Transform& l_transform = m_GameObject.m_Transform;
			glm::mat4 l_mat4SpriteModel = glm::mat4(1.0f);
			l_mat4SpriteModel = glm::translate(l_mat4SpriteModel, l_transform.getPosition());

			l_mat4SpriteModel = glm::scale(l_mat4SpriteModel, l_CurrentSprite.getSpriteDimensions());
			l_CurrentShader.setUniforMat4fv(Sprite::UNIFORM_MODEL_MATRIX, l_mat4SpriteModel);

			glActiveTexture(GL_TEXTURE0);
			l_CurrentSprite.getTexture()->bind();

			l_CurrentShader.setUniform1i(Sprite::UNIFORM_TEXTURE_SAMPLER, 0);

			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
}