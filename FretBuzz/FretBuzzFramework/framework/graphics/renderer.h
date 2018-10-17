#pragma once
#include "../graphics/shader.h"
#include <vector>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class IRenderer
		{
		protected:
			struct VertexData
			{
				glm::vec4 m_v4Position;
				glm::vec4 m_v4Color;
				glm::vec2 m_v2UV;
				float m_fTextureID;
			};

			static constexpr int INDEX_VERTEX = 0;
			static constexpr int INDEX_COLOR = 1;
			static constexpr int INDEX_TEX_UV = 2;
			static constexpr int INDEX_TEX_ID = 3;

			static constexpr int TOTAL_TEXTURE_SLOTS = 32;
			static constexpr int SIZE_OF_VERTEX_DATA = sizeof(VertexData);

			static constexpr GLint s_arrTextureIDArray[TOTAL_TEXTURE_SLOTS] =
			{
				0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
				17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
			};

			static constexpr char UNIFORM_TEXTURE_SAMPLER[] = "textureSampler";

			std::vector<unsigned int> m_vectActiveTexIDs;

			GLuint m_IBO = 0;
			GLuint m_VBO = 0;
			GLuint m_VAO = 0;

			static constexpr int SIZE_OF_SINGLE_INDEX = sizeof(GLuint);

			unsigned int m_iIndexBufferSize = 0;
			unsigned int m_iTotalIndices = 0;
			unsigned int m_iVertBufferSize = 0;

			GLuint* m_pIndexBufferArray = nullptr;

			IRenderer();

		public:
			virtual ~IRenderer() = 0;

			inline int getVertBufferSize() const
			{
				return m_iVertBufferSize;
			}

			inline int getIndexBufferSize() const
			{
				return m_iIndexBufferSize;
			}
		};
	}
}