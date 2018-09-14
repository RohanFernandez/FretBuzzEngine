#pragma once
#include "../../system/component.h"
#include "../sprite.h"
#include "../../graphics/shader.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class GameObject;
		class SpriteRenderer : public ns_system::IComponent
		{
		private:
			SpriteRenderer(ns_system::GameObject& a_GameObj);
			SpriteRenderer(ns_system::GameObject& a_GameObj, Sprite* a_Sprite, Shader* a_pShader);
			SpriteRenderer(ns_system::GameObject& a_GameObj, std::string a_strSpriteID);
			SpriteRenderer(ns_system::GameObject& a_GameObj, glm::vec4 a_v4Color, glm::vec2 a_v2Dimensions);

			Sprite* m_pSprite = nullptr;
			Shader* m_pShader = nullptr;

			Sprite m_DefaltSprite;

			/*GLuint m_IBO;
			GLuint m_VBO;
			GLuint m_VAO;*/

			void initialize();

		protected:
			~SpriteRenderer();

		public:
			static SpriteRenderer* addToGameObject(ns_system::GameObject& a_GameObj);
			static SpriteRenderer* addToGameObject(ns_system::GameObject& a_GameObj, Sprite* a_Sprite, Shader* a_pShader = nullptr);
			static SpriteRenderer* addToGameObject(ns_system::GameObject& a_GameObj, std::string a_strSpriteID);
			static SpriteRenderer* addToGameObject(ns_system::GameObject& a_GameObj, glm::vec4 a_v4Color, glm::vec2 a_v2Dimensions);

			void setSprite(Sprite* a_Sprite);
			void setSprite(std::string a_strSpriteID);

			void setShader(std::string a_strShaderId);
			void setShader(Shader* a_pShader);

			void setDefaultColor(glm::vec4 a_v4Color)
			{
				m_DefaltSprite.setColor(a_v4Color);
			}

			void setDefaultDimensions(glm::vec2 a_v2Dimensions)
			{
				m_DefaltSprite.setDimensions({a_v2Dimensions,0.0f});
			}

			virtual void render(const glm::mat4& a_mat4Transformation, const ns_system::Viewport& a_Camera) override;
		};
	}
}