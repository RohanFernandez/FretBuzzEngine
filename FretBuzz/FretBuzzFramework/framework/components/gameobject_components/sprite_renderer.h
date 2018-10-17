#pragma once
#include "../../system/component.h"
#include "../sprite.h"
#include "../../graphics/material.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class GameObject;
		class SpriteRenderer : public ns_system::IComponent
		{
		private:
			SpriteRenderer(ns_system::GameObject& a_GameObj);
			SpriteRenderer(ns_system::GameObject& a_GameObj, Sprite* a_Sprite);
			SpriteRenderer(ns_system::GameObject& a_GameObj, std::string a_strSpriteID);
			SpriteRenderer(ns_system::GameObject& a_GameObj, glm::vec4 a_v4Color, glm::vec2 a_v2Dimensions);

			Sprite* m_pSprite = nullptr;

			Sprite m_DefaultSprite;

		protected:
			~SpriteRenderer();

			Material m_Material;

		public:
			static SpriteRenderer* addToGameObject(ns_system::GameObject& a_GameObj);
			static SpriteRenderer* addToGameObject(ns_system::GameObject& a_GameObj, Sprite* a_Sprite);
			static SpriteRenderer* addToGameObject(ns_system::GameObject& a_GameObj, std::string a_strSpriteID);
			static SpriteRenderer* addToGameObject(ns_system::GameObject& a_GameObj, glm::vec4 a_v4Color, glm::vec2 a_v2Dimensions);

			void setSprite(Sprite* a_Sprite);
			void setSprite(std::string a_strSpriteID);

			void setDefaultColor(glm::vec4 a_v4Color)
			{
				m_DefaultSprite.setColor(a_v4Color);
			}

			void setDefaultDimensions(glm::vec2 a_v2Dimensions)
			{
				m_DefaultSprite.setDimensions({a_v2Dimensions,0.0f});
			}

			virtual void render(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera) override;
		};
	}
}