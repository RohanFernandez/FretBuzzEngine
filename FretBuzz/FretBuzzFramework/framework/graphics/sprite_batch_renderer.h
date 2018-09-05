#pragma once
#include "renderer.h"
#include "../utils/math.h"
#include "../components/sprite.h"
#include <vector>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class SpriteBatchRenderer : public IRenderer
		{
		private:
			static SpriteBatchRenderer* s_pInstance;

			struct VertexData
			{
				glm::vec4 m_v4Position;
				glm::vec4 m_v4Color;
				glm::vec2 m_v2UV;
				float m_fTextureID;
			};

			static constexpr int TOTAL_TEXTURE_SLOTS = 32;
			static constexpr GLint s_arrTextureIDArray[TOTAL_TEXTURE_SLOTS] =
			{
				0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
				17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
			};

			std::vector<unsigned int> m_vectActiveTexIDs;

			GLuint* m_pIndexBufferArray = nullptr;

			VertexData* m_pCurrentVertexData = nullptr;

			int m_iIndicesToDraw = 0;
			Shader* m_pCurrentShader = nullptr;

		public:


			static constexpr int SIZE_OF_VERTEX_DATA = sizeof(VertexData);

			static constexpr int VERTICES_PER_SPRITE = 4;
			static constexpr int INDICES_PER_SPRITE = 6;
			
			static constexpr int INDEX_VERTEX = 0;
			static constexpr int INDEX_COLOR = 1;
			static constexpr int INDEX_TEX_UV = 2;
			static constexpr int INDEX_TEX_ID = 3;


			SpriteBatchRenderer(int a_iMaxSprites);
			~SpriteBatchRenderer();
			
			static void submit(const Sprite& a_Sprite, const glm::mat4& a_mat4Transformation, Shader* a_pShader);
			static void begin();
			static void end();
			static void flush();
		};
	}
}