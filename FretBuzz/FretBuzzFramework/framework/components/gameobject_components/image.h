#pragma once
#include "../../system/component_2d.h"
#include "../sprite.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class GameObject2D;
		class Image : public ns_system::IComponent2D
		{
		protected:
			Image(ns_system::GameObject2D& a_GameObject2D, Sprite* a_pSprite, bool a_bIsEnabled);
			virtual ~Image();
			Sprite* m_pSprite = nullptr;
			glm::vec2& m_v2Dimensions;

		public:
			static Image* addToGameObject(ns_system::GameObject2D& a_GameObject2D, Sprite* a_pSprite, bool a_bIsEnabled = true);
			void setSprite(Sprite* a_pSpite);

			virtual void render(const glm::mat4& a_mat4Transformation, const ns_system::Camera& a_Camera) override;
		};
	}
}