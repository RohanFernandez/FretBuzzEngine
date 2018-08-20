#pragma once
#include <vector>
#include "../../graphics/texture.h"
#include "../../utils/math.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class SpriteData
		{
		public:
			static constexpr int s_INDICES[6] = {0, 2, 1, 0, 3, 2};
			static constexpr int s_VERT_COUNT = 4;
			glm::vec2 m_Vertices[s_VERT_COUNT] = {};

			SpriteData(glm::vec2 a_v2SpriteCoords, glm::vec2 a_v2DimensionsWH, glm::vec2 a_v2TexDimensionsWH)
				: m_Vertices
			{ { a_v2SpriteCoords.x / a_v2TexDimensionsWH.x, (a_v2SpriteCoords.y + a_v2DimensionsWH.y) / a_v2TexDimensionsWH.y },					   //0
			  { a_v2SpriteCoords.x / a_v2TexDimensionsWH.x, a_v2SpriteCoords.y / a_v2TexDimensionsWH.y },											   //1
			  {(a_v2SpriteCoords.x + a_v2DimensionsWH.x) / a_v2TexDimensionsWH.x, a_v2SpriteCoords.y / a_v2TexDimensionsWH.y },						   //2
			  { (a_v2SpriteCoords.x + a_v2DimensionsWH.x) / a_v2TexDimensionsWH.x, (a_v2SpriteCoords.y + a_v2DimensionsWH.y) / a_v2TexDimensionsWH.y } //3
			} {}

			SpriteData(SpriteData& a_SpriteData)
			{
				memcpy_s(m_Vertices, s_VERT_COUNT, a_SpriteData.m_Vertices, s_VERT_COUNT);
			}

			SpriteData(SpriteData&& a_SpriteData)
			{
				memcpy_s(m_Vertices, s_VERT_COUNT, a_SpriteData.m_Vertices, s_VERT_COUNT);
			}

			void operator=(SpriteData a_SpriteData)
			{
				memcpy_s(m_Vertices, s_VERT_COUNT, a_SpriteData.m_Vertices, s_VERT_COUNT);
			}
		};

		class Sprite : public ns_system::IManagedResource
		{
		private:
			std::vector<SpriteData> m_vectSpriteData;
			Texture m_Texture;
			virtual void destroyResource() override;

		public:
			Sprite() = delete;
			Sprite(Texture& a_Texture, std::vector<SpriteData> a_vectSpriteData);
			Sprite(Sprite& a_Sprite);
			Sprite(Sprite&& a_Sprite);

			~Sprite();

			const std::vector<SpriteData> getSpriteData() const;
			void operator=(Sprite& a_Sprite);
			void operator=(Sprite&& a_Sprite);
		};
	}
}