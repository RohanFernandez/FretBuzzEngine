#pragma once
#include "data_texture.h"
#include "../utils/math.h"
#include "material.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class PostProcessManager
		{
		private:
			static PostProcessManager* s_pInstance;

			bool m_bIsPostProcessOn = true;

		public:
			PostProcessManager(unsigned int a_iWidth, unsigned int a_iHeight);
			virtual ~PostProcessManager();

			void bind() const;
			void unbind() const;

			void begin() const;
			void draw(unsigned int a_uiFrameBufferID, const Camera& a_MainCamera) const;

			static PostProcessManager* initialize(unsigned int a_iWidth, unsigned int a_iHeight);
			void destroy();
			static const PostProcessManager* get();

			static constexpr int SIZE_SINGLE_VERTEX_DATA = 4 * sizeof(GLfloat);

			Material m_Material;

		static constexpr float RENDER_QUAD_DATA[24]
		{
			-1.0f,  1.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, 1.0f, 0.0f,

			-1.0f,  1.0f, 0.0f, 1.0f,
			 1.0f, -1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, 1.0f, 1.0f
		};

			unsigned int m_FBO;
			unsigned int m_RBO;

			unsigned int m_ScreenQuadVAO;
			unsigned int m_ScreenQuadVBO;

			DataTexture m_DataTexture;

			void togglePostProcess(bool a_bIsPostProcessOn);
			bool isPostProcessActive() const;
		};
	}
}