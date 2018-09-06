#pragma once
#include <vector>
#include "../graphics/texture.h"
#include "../utils/math.h"

#include "../system/game_object.h"
#include "camera.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Sprite
		{
		private:
			Texture* m_pTexture = nullptr;
			std::vector<glm::vec2> m_TexCoords;
			std::vector<glm::vec4> m_VertPosition;
			glm::vec3 m_SpriteDimensionWH;
			glm::vec2 m_OriginOffset = {0.0f, 0.0f};

			glm::vec4 m_v4Color;

			std::string m_strID;

		public:
			Sprite(std::string a_strID, glm::vec2 a_v2SpriteCoords, glm::vec2 a_v2DimensionsWH, glm::vec2 a_v2TexDimensionsWH, glm::vec2 a_v2OriginOffset, Texture* a_pTexture, glm::vec4 a_v4Color = { 0.996, 0.180, 1.0,1.0 })
				:
				m_strID{a_strID},
				m_pTexture{ a_pTexture },
				m_SpriteDimensionWH{ a_v2DimensionsWH, 0.0f },
				m_OriginOffset{a_v2OriginOffset},
				m_v4Color{a_v4Color},
				m_TexCoords{
							 { a_v2SpriteCoords.x / a_v2TexDimensionsWH.x, (a_v2TexDimensionsWH.y - (a_v2SpriteCoords.y + a_v2DimensionsWH.y)) / a_v2TexDimensionsWH.y },					       //0
							 { a_v2SpriteCoords.x / a_v2TexDimensionsWH.x, (a_v2TexDimensionsWH.y - a_v2SpriteCoords.y) / a_v2TexDimensionsWH.y },											   //1
							 {(a_v2SpriteCoords.x + a_v2DimensionsWH.x) / a_v2TexDimensionsWH.x, (a_v2TexDimensionsWH.y - a_v2SpriteCoords.y) / a_v2TexDimensionsWH.y },						   //2
							 {(a_v2SpriteCoords.x + a_v2DimensionsWH.x) / a_v2TexDimensionsWH.x, (a_v2TexDimensionsWH.y - (a_v2SpriteCoords.y + a_v2DimensionsWH.y)) / a_v2TexDimensionsWH.y }    //3
							},

				m_VertPosition{
								 glm::vec4(-0.5 * a_v2DimensionsWH.x + a_v2OriginOffset.x, -0.5 * a_v2DimensionsWH.y + a_v2OriginOffset.y, 0.0, 1.0f ),
								 glm::vec4(-0.5 * a_v2DimensionsWH.x + a_v2OriginOffset.x, 0.5 * a_v2DimensionsWH.y + a_v2OriginOffset.y, 0.0, 1.0f),
								 glm::vec4(0.5 * a_v2DimensionsWH.x + a_v2OriginOffset.x, 0.5 * a_v2DimensionsWH.y + a_v2OriginOffset.y, 0.0, 1.0f),
								 glm::vec4(0.5 * a_v2DimensionsWH.x + a_v2OriginOffset.x, -0.5 * a_v2DimensionsWH.y + a_v2OriginOffset.y, 0.0, 1.0f)
							}
								{
				
								}

			Sprite(glm::vec2 a_v2Dimensions = {1.0f, 1.0f}, glm::vec4 a_v4Color = {0.996, 0.180, 1.0,1.0})
				: m_SpriteDimensionWH{ a_v2Dimensions,0.0f },
				m_v4Color{ a_v4Color },

				m_TexCoords{
								{ 0.0f, 0.0f },  //0
								{ 0.0f, 1.0f },  //1
								{ 1.0f, 1.0f },  //2
								{ 1.0f, 0.0f }   //3
							},

				m_VertPosition{
								glm::vec4(-0.5 * a_v2Dimensions.x, -0.5 * a_v2Dimensions.y, 0.0, 1.0f),
								glm::vec4(-0.5 * a_v2Dimensions.x, 0.5 * a_v2Dimensions.y, 0.0, 1.0f),
								glm::vec4(0.5 * a_v2Dimensions.x, 0.5 * a_v2Dimensions.y, 0.0, 1.0f),
								glm::vec4(0.5 * a_v2Dimensions.x, -0.5 * a_v2Dimensions.y, 0.0, 1.0f)
							}
			{
			
			}

			Sprite(std::string a_strID, glm::vec2 a_v2SpriteCoords, glm::vec2 a_v2DimensionsWH, glm::vec2 a_v2TexDimensionsWH, Texture* a_pTexture)
				: Sprite(a_strID, a_v2SpriteCoords, a_v2DimensionsWH, a_v2TexDimensionsWH, {0.0f, 0.0f}, a_pTexture)
			{
			
			}

			Sprite(std::string a_strID, glm::vec2 a_v2SpriteCoords, glm::vec2 a_v2DimensionsWH, glm::vec2 a_v2TexDimensionsWH, glm::vec4 a_Color)
				: 
				Sprite(a_strID, a_v2SpriteCoords, a_v2DimensionsWH, a_v2TexDimensionsWH, { 0.0f, 0.0f }, 0, a_Color)
			{
			}

			Sprite(Sprite& a_SpriteData)
				:
				m_strID{ a_SpriteData.m_strID },
				m_pTexture{ a_SpriteData.m_pTexture },
				m_SpriteDimensionWH{ a_SpriteData.m_SpriteDimensionWH },
				m_OriginOffset{ a_SpriteData.m_OriginOffset},
				m_v4Color{ a_SpriteData.m_v4Color},
				m_TexCoords{ a_SpriteData.m_TexCoords[0],
							 a_SpriteData.m_TexCoords[1],
							 a_SpriteData.m_TexCoords[2],
							 a_SpriteData.m_TexCoords[3] },

				m_VertPosition{ a_SpriteData.m_VertPosition[0],
								a_SpriteData.m_VertPosition[1],
								a_SpriteData.m_VertPosition[2],
								a_SpriteData.m_VertPosition[3]
							  }	
								{
								}

			Sprite(Sprite&& a_SpriteData)
				: 
				m_strID{ a_SpriteData.m_strID },
				m_pTexture{ a_SpriteData.m_pTexture },
				m_OriginOffset{ a_SpriteData.m_OriginOffset },
				m_SpriteDimensionWH{ a_SpriteData.m_SpriteDimensionWH},
				m_v4Color{ a_SpriteData.m_v4Color },
				m_TexCoords{ a_SpriteData.m_TexCoords[0],
							a_SpriteData.m_TexCoords[1],
							a_SpriteData.m_TexCoords[2],
							a_SpriteData.m_TexCoords[3] },

				m_VertPosition{ a_SpriteData.m_VertPosition[0],
								a_SpriteData.m_VertPosition[1],
								a_SpriteData.m_VertPosition[2],
								a_SpriteData.m_VertPosition[3]}
							{
							}

			~Sprite()
			{
				m_pTexture = nullptr;
			}

			void operator=(Sprite& a_SpriteData)
			{
				m_strID = a_SpriteData.m_strID ;
				m_pTexture = a_SpriteData.m_pTexture;
				m_TexCoords = a_SpriteData.m_TexCoords;
				m_VertPosition = a_SpriteData.m_VertPosition;
				m_SpriteDimensionWH = a_SpriteData.m_SpriteDimensionWH;
				m_OriginOffset = a_SpriteData.m_OriginOffset;
				m_v4Color = a_SpriteData.m_v4Color;
			}

			const Texture* getTexture() const
			{
				return m_pTexture;
			}

			const std::vector<glm::vec2>& getTexCoords() const
			{
				return m_TexCoords;
			}

			const std::vector<glm::vec4>& getVertPosition() const
			{
				return m_VertPosition;
			}

			inline const glm::vec3& getSpriteDimensions() const
			{
				return m_SpriteDimensionWH;
			}

			inline std::string getID() const
			{
				return m_strID;
			}

			inline const glm::vec4& getColor() const
			{
				return m_v4Color;
			}

			inline void setColor(glm::vec4 a_v4Color)
			{
				m_v4Color = a_v4Color;
			}

			inline void setDimensions(glm::vec3 a_v3Dimensions)
			{
				m_SpriteDimensionWH = a_v3Dimensions;
				m_VertPosition = {
					glm::vec4(-0.5 * m_SpriteDimensionWH.x, -0.5 * m_SpriteDimensionWH.y, 0.0, 1.0f),
					glm::vec4(-0.5 * m_SpriteDimensionWH.x, 0.5 * m_SpriteDimensionWH.y, 0.0, 1.0f),
					glm::vec4(0.5 * m_SpriteDimensionWH.x, 0.5 * m_SpriteDimensionWH.y, 0.0, 1.0f),
					glm::vec4(0.5 * m_SpriteDimensionWH.x, -0.5 * m_SpriteDimensionWH.y, 0.0, 1.0f)
				};
			}
		};

		class SpriteGroup : public ns_system::IManagedResource
		{

		protected:
			std::vector<Sprite> m_vectSpriteData;
			Texture* m_pTexture = nullptr;

			virtual void destroyResource() override;

		public:
			SpriteGroup() = delete;
			SpriteGroup(Texture* a_pTexture, std::vector<Sprite> a_vectSpriteData);
			SpriteGroup(SpriteGroup& a_SpriteSheet);
			SpriteGroup(SpriteGroup&& a_SpriteSheet);

			~SpriteGroup();

			std::vector<Sprite>* getSprites();
			Sprite* getSprite(int l_iSpriteIndex);
			Sprite* getSpriteByID(std::string l_strSpriteID);

			void operator=(SpriteGroup& a_SpriteSheet);
			void operator=(SpriteGroup&& a_SpriteSheet);

			inline int getSpriteCount() const
			{
				return m_vectSpriteData.size();
			}
		};
	}
}