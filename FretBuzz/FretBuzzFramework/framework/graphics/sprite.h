#pragma once
#include <vector>
#include "../graphics/texture.h"
#include "../utils/math.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		struct SpriteData
		{
			glm::vec2 m_v2TexCoords;

			SpriteData(glm::vec2 a_v2TexCoords)
				: m_v2TexCoords{ a_v2TexCoords }{}

			SpriteData(SpriteData& a_SpriteData)
				: m_v2TexCoords{ a_SpriteData.m_v2TexCoords }{}
		};

		class Sprite
		{
		private:
			std::vector<SpriteData> m_vectSpriteData;
			Texture m_Texture;

		public:
			Sprite() = delete;
			Sprite(int a_iTextureID, Texture a_Texture, std::vector<SpriteData> a_vectSpriteData);
			Sprite(Sprite& a_Sprite);
			Sprite(Sprite&& a_Sprite);

			~Sprite();

			const std::vector<SpriteData> getSpriteData() const;
			void operator=(Sprite a_Sprite);
		};
	}
}