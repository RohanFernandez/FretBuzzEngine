#pragma once
#include "system/component_2d.h"
#include "../sprite.h"
#include "graphics/material.h"

namespace ns_fretBuzz
{
	class GameObject2D;
	class  Image : public IComponent2D
	{
	protected:
		virtual ~Image();
		Sprite* m_pSprite = nullptr;
		Shader* m_pShader = nullptr;

		glm::vec4 m_Color = {1.0f, 1.0f, 1.0f, 1.0f};

		static const std::vector<glm::vec2> s_vectTexcoords;

		Material m_Material;

	public:
		Image(GameObject2D* a_GameObject2D, Sprite* a_pSprite, glm::vec4 a_v4Color,  bool a_bIsEnabled = true);
		void setSprite(Sprite* a_pSpite);

		virtual void render(const glm::mat4& a_mat4Transformation, const Camera& a_Camera) override;

		void setShader(Shader* a_pShader);

		void setColor(glm::vec4 a_Color);
		const glm::vec4& getColor(glm::vec4 a_Color) const;
	};
}