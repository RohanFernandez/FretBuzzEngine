#pragma once
#include "batch_renderer_manager.h"
#include <fretbuzz.h>

namespace ns_fretBuzz
{
	struct  LineData
	{
		LineData() {}

		LineData(glm::vec4 a_v4StartPosition, glm::vec4 a_v4StartColor,
				glm::vec4 a_v4EndPosition, glm::vec4 a_v4EndColor)
			: 
			m_v4StartPosition{ a_v4StartPosition },
			m_v4StartColor{ a_v4StartColor },

			m_v4EndPosition{ a_v4EndPosition },
			m_v4EndColor{ a_v4EndColor }
		{}

		glm::vec4 m_v4StartPosition{};
		glm::vec4 m_v4StartColor{};

		glm::vec4 m_v4EndPosition{};
		glm::vec4 m_v4EndColor{};
	};

	class LineBatchRenderer : public IBatchRenderer
	{
	protected:
		static LineBatchRenderer* s_pInstance;

		GLuint* m_pIndexBufferArray = nullptr;

		struct VertexData
		{
			glm::vec4 m_v4Position;
			glm::vec4 m_v4Color;
		};

		VertexData* m_pCurrentVertexData = nullptr;
		const unsigned int MAX_LINES = 0;
		unsigned int m_iLinesInBatch = 0;

		int m_iIndicesToDraw = 0;

		float m_fLineWidth = 1.0f;

		LineBatchRenderer(unsigned int a_iMaxLines, float a_fLineWidth = 1.0f);
		~LineBatchRenderer();

	public:

		static constexpr int SIZE_OF_VERTEX_DATA = sizeof(VertexData);

		static constexpr int VERTICES_PER_LINE = 2;
		static constexpr int INDICES_PER_LINE = 2;

		static constexpr int INDEX_VERTEX = 0;
		static constexpr int INDEX_COLOR = 1;

		static LineBatchRenderer* initialize(unsigned int a_iMaxLines, float a_fLineWidth = 1.0f);
		virtual void destroy() override;

		static void submit(const LineData* a_pLine, const int a_iNumOfLines, const glm::mat4& a_mat4Transformation, Material& a_Material);

		virtual void begin() override;
		virtual void end() override;
		virtual void flush() override;
	};
}