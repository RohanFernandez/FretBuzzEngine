#pragma once
#include <vector>
#include "../../graphics/texture.h"
#include "../../graphics/shader.h"
#include "../../utils/math.h"

#include "../../game/game_object.h"
#include "../camera/camera.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Sprite
		{
		public:
			static constexpr char UNIFORM_PROJECTION_MATRIX[] = "unifProjection";
			static constexpr char UNIFORM_VIEW_MATRIX[] = "unifView";
			static constexpr char UNIFORM_MODEL_MATRIX[] = "unifModel";
			static constexpr char UNIFORM_TEXTURE_SAMPLER[] = "textureSampler";

			static constexpr int s_INDICES[6] = { 0, 2, 1, 0, 3, 2 };
			static constexpr int s_VERT_COUNT = 4;
			static constexpr glm::vec3 s_VERTICES[s_VERT_COUNT] =
			{
				{ -0.5, -0.5, 0.0 },
				{ -0.5, 0.5, 0.0 },
				{ 0.5, 0.5, 0.0 },
				{ 0.5, -0.5, 0.0 }
			};


		private:
			Texture * m_pTexture = nullptr;
			Shader* m_pShader = nullptr;
			std::vector<glm::vec2> m_TexCoords;

		public:
			Sprite(glm::vec2 a_v2SpriteCoords, glm::vec2 a_v2DimensionsWH, glm::vec2 a_v2TexDimensionsWH, Texture* a_pTexture, Shader* a_pShader)
				:
				m_pShader{ a_pShader },
				m_pTexture{ a_pTexture },
				m_TexCoords{ { a_v2SpriteCoords.x / a_v2TexDimensionsWH.x, (a_v2SpriteCoords.y + a_v2DimensionsWH.y) / a_v2TexDimensionsWH.y },					       //0
							 { a_v2SpriteCoords.x / a_v2TexDimensionsWH.x, a_v2SpriteCoords.y / a_v2TexDimensionsWH.y },											   //1
							 {(a_v2SpriteCoords.x + a_v2DimensionsWH.x) / a_v2TexDimensionsWH.x, a_v2SpriteCoords.y / a_v2TexDimensionsWH.y },						   //2
							 { (a_v2SpriteCoords.x + a_v2DimensionsWH.x) / a_v2TexDimensionsWH.x, (a_v2SpriteCoords.y + a_v2DimensionsWH.y) / a_v2TexDimensionsWH.y } }//3 
							 {}


			Sprite(Sprite& a_SpriteData)
				: m_pShader{ a_SpriteData.m_pShader },
				  m_pTexture{ a_SpriteData.m_pTexture },
				m_TexCoords{ a_SpriteData .m_TexCoords[0],
							 a_SpriteData.m_TexCoords[1],
							 a_SpriteData.m_TexCoords[2],
							 a_SpriteData.m_TexCoords[3] }
			{
				
			}

			Sprite(Sprite&& a_SpriteData)
				: m_pShader{ a_SpriteData.m_pShader },
				  m_pTexture{ a_SpriteData.m_pTexture },
				m_TexCoords{ a_SpriteData.m_TexCoords[0],
							a_SpriteData.m_TexCoords[1],
							a_SpriteData.m_TexCoords[2],
							a_SpriteData.m_TexCoords[3] }
			{
				
			}

			~Sprite()
			{
				m_pShader = nullptr;
				m_pTexture = nullptr;
			}

			void operator=(Sprite& a_SpriteData)
			{
				m_pShader = a_SpriteData.m_pShader;
				m_pTexture = a_SpriteData.m_pTexture;
				m_TexCoords = a_SpriteData.m_TexCoords;
			}

			const Texture* getTexture() const
			{
				return m_pTexture;
			}

			const Shader* getShader() const
			{
				return m_pShader;
			}

			const std::vector<glm::vec2>& getTexCoords() const
			{
				return m_TexCoords;
			}
		};

		class SpriteSheet : public ns_system::IManagedResource
		{

		protected:
			std::vector<Sprite> m_vectSpriteData;
			Texture* m_pTexture = nullptr;
			Shader* m_pShader = nullptr;

			GLuint m_IBO;
			GLuint m_VBO;
			GLuint m_VAO;

			virtual void destroyResource() override;

		public:
			SpriteSheet() = delete;
			SpriteSheet(Texture* a_pTexture, Shader* a_pShader, std::vector<Sprite> a_vectSpriteData);
			SpriteSheet(SpriteSheet& a_SpriteSheet);
			SpriteSheet(SpriteSheet&& a_SpriteSheet);

			~SpriteSheet();

			std::vector<Sprite>* getSprites();
			Sprite* getSprite(int l_iSpriteIndex);

			void operator=(SpriteSheet& a_SpriteSheet);
			void operator=(SpriteSheet&& a_SpriteSheet);
		};
	}
}