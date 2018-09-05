#pragma once
#include "../graphics/shader.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class IRenderer
		{
		protected:
			IRenderer();

			GLuint m_IBO = 0;
			GLuint m_VBO = 0;
			GLuint m_VAO = 0;

			static constexpr int SIZE_OF_SINGLE_INDEX = sizeof(GLuint);

			unsigned int m_iIndexBufferSize = 0;
			unsigned int m_iTotalIndices = 0;

			unsigned int m_iVertBufferSize = 0;

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