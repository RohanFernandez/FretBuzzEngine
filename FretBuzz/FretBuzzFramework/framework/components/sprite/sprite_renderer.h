#pragma once
#include "../../game/component.h"
#include "sprite.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class GameObject;
		class SpriteRenderer : public ns_system::IComponent
		{
		private:
			static constexpr ns_system::COMPONENT_TYPE s_COMPONENT_TYPE = ns_system::COMPONENT_TYPE::SPRITE_RENDERER;

			SpriteRenderer(ns_system::GameObject& a_GameObj);
			SpriteRenderer(ns_system::GameObject& a_GameObj, Sprite* a_Sprite);
			SpriteRenderer(ns_system::GameObject& a_GameObj, std::string a_strSpriteID);

			~SpriteRenderer();

			Sprite* m_pSprite = nullptr;

			struct SpriteAttributes
			{
				glm::vec3 m_v3Position;
				glm::vec2 m_v2TexCoords;
			};
			
			bool m_bIsAllowedToRender = true;

			GLuint m_IBO;
			GLuint m_VBO;
			GLuint m_VAO;

			void initialize();

		public:
			static SpriteRenderer* addToGameObject(ns_system::GameObject& a_GameObj);
			static SpriteRenderer* addToGameObject(ns_system::GameObject& a_GameObj, Sprite* a_Sprite);

			void setSprite(Sprite* a_Sprite);
			void setSprite(std::string a_strSpriteID);

			virtual void render(const ns_system::Camera& a_Camera) override;

			inline bool getIsRendering() const
			{
				return m_bIsAllowedToRender;
			}

			inline void setIsRendering(bool a_bIsAllowedToRender)
			{
				m_bIsAllowedToRender = a_bIsAllowedToRender;
			}
		};
	}
}