#pragma once
#include "material.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class FRETBUZZ_API IRenderer
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

			static constexpr int SIZE_OF_VERTEX_DATA = sizeof(VertexData);

			std::vector<unsigned int> m_vectActiveTexIDs;

			GLuint m_IBO = 0;
			GLuint m_VBO = 0;
			GLuint m_VAO = 0;

			static constexpr int SIZE_OF_SINGLE_INDEX = sizeof(GLuint);

			unsigned int m_iIndexBufferSize = 0;
			unsigned int m_iTotalIndices = 0;
			unsigned int m_iVertBufferSize = 0;

			glm::mat4 m_mat4Transformation;

			IRenderer();

			Material m_Material;

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