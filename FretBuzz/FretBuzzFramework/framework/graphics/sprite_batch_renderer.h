#pragma once
#include "batch_renderer_manager.h"
#include "../utils/math.h"
#include "../components/sprite.h"
#include <vector>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class SpriteBatchRenderer : public IBatchRenderer
		{
		protected:
			static SpriteBatchRenderer* s_pInstance;

			VertexData* m_pCurrentVertexData = nullptr;

			const unsigned int MAX_SPRITES = 0;
			unsigned int m_iSpritesInBatch = 0;

			int m_iIndicesToDraw = 0;
			Shader* m_pCurrentShader = nullptr;

			SpriteBatchRenderer(unsigned int a_iMaxSprites);
			~SpriteBatchRenderer();

		public:
			static SpriteBatchRenderer* initialize(unsigned int a_iMaxSprites);
			void destroy();

			static constexpr int VERTICES_PER_SPRITE = 4;
			static constexpr int INDICES_PER_SPRITE = 6;

			static void submit(const Sprite& a_Sprite, const glm::mat4& a_mat4Transformation, Shader* a_pShader);
			static void submit(const std::vector<glm::vec4>& a_vectPosition, const glm::vec4& l_v4Color,
				const Texture* a_pTexture, const std::vector<glm::vec2>& l_vectv2TexCoords,
				const glm::mat4& a_mat4Transformation, Shader* a_pShader);

			virtual void begin() override;
			virtual void end() override;
			virtual void flush() override;
		};
	}
}