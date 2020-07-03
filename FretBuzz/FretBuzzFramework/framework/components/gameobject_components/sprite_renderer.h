#pragma once
#include "../sprite.h"
#include "system/component.h"
#include "graphics/material.h"
#include "graphics/renderer.h"

namespace ns_fretBuzz
{
	class GameObject;
	class  SpriteRenderer : public IComponent, public IRenderer
	{
	private:

		Sprite* m_pSprite = nullptr;

		Sprite m_DefaultSprite;

	protected:
		~SpriteRenderer();

	public:
		SpriteRenderer(GameObject* a_GameObj);
		SpriteRenderer(GameObject* a_GameObj, Sprite* a_Sprite);
		SpriteRenderer(GameObject* a_GameObj, std::string a_strSpriteID);
		SpriteRenderer(GameObject* a_GameObj, glm::vec4 a_v4Color, glm::vec2 a_v2Dimensions);

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

		virtual void render(const glm::mat4& a_mat4Transformation, const Camera& a_Camera) override;
	};
}