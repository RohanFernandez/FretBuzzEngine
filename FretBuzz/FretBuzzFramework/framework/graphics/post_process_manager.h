#pragma once
#include "data_texture.h"
#include "material.h"

namespace FRETBUZZ
{
	class  PostProcessManager
	{
	private:
		static PostProcessManager* s_pInstance;

		unsigned int m_FBO = 0;
		unsigned int m_RBO = 0;

		unsigned int m_ScreenQuadVAO = 0;
		unsigned int m_ScreenQuadVBO = 0;

		static constexpr float RENDER_QUAD_DATA[24]
		{
			-1.0f,  1.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f,
				1.0f, -1.0f, 1.0f, 0.0f,

			-1.0f,  1.0f, 0.0f, 1.0f,
				1.0f, -1.0f, 1.0f, 0.0f,
				1.0f,  1.0f, 1.0f, 1.0f
		};

		bool m_bIsPostProcessOn = true;

		bool isSetupFrameBufferSuccess(unsigned int a_uiWidth, unsigned int a_uiHeight);

		virtual ~PostProcessManager();

	public:
		PostProcessManager(unsigned int a_iWidth, unsigned int a_iHeight, Material::POST_PROCESS_TYPE a_PostProcessType);

		void bind() const;
		void unbind() const;

		void begin() const;
		void draw(unsigned int a_uiFrameBufferID, const Camera& a_MainCamera) const;

		static PostProcessManager* initialize(unsigned int a_iWidth, unsigned int a_iHeight, Material::POST_PROCESS_TYPE a_PostProcessType = Material::POST_PROCESS_TYPE::EDGE_DETECT);
		void destroy();
		static const PostProcessManager* get();

		static constexpr int SIZE_SINGLE_VERTEX_DATA = 4 * sizeof(GLfloat);

		Material m_Material;
		DataTexture m_DataTexture;
		void windowResize(int a_iWidth, int a_iHeight);

		static void togglePostProcess(bool a_bIsPostProcessOn);
		static bool isPostProcessActive();
		static void setPostProcessType(Material::POST_PROCESS_TYPE a_PostProcessType);
	};
}