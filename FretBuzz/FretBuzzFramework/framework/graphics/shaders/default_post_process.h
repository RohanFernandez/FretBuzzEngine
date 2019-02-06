#pragma once

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Material;
		class Camera;
		class Shader;

		class FRETBUZZ_API DefaultPostProcess : Shader
		{
		private:
			static DefaultPostProcess* s_pInstance;

			DefaultPostProcess(std::string a_strShaderName);
			virtual ~DefaultPostProcess();

			static constexpr char UNIF_SCREEN_TEXTURE[] = "screenTexture";
			static constexpr int UNIF_SCREEN_TEXTURE_SAMPLE_ID = 0;
			static constexpr char UNIF_ARRAY_KERNEL[] = "arrKernel";

			static constexpr int s_iKERNEL_SIZE = 9;

			//Sharpen Kernel
			static constexpr float s_arrSharpenKernel[s_iKERNEL_SIZE] =
			{
				-1.0, -1.0, -1.0,
				-1.0,  9.0, -1.0,
				-1.0, -1.0, -1.0
			};

			//Blur Kernel
			static constexpr float s_arrBlurKernel[s_iKERNEL_SIZE] =
			{
				1.0 / 16, 2.0 / 16, 1.0 / 16,
				2.0 / 16, 4.0 / 16, 2.0 / 16,
				1.0 / 16, 2.0 / 16, 1.0 / 16
			};

			//Edge detection Kernel
			static constexpr float s_arrEdgeDetectKernel[s_iKERNEL_SIZE] =
			{
				1.0,  1.0, 1.0,
				1.0, -8.0, 1.0,
				1.0,  1.0, 1.0
			};

		public:
			static DefaultPostProcess* initialize(std::string a_strShaderPath);
			virtual void bind(const Material& a_Material, const Camera& a_Camera) const override;
			virtual void destroy() override;

			static const float* getKernel(Material a_PostProcessType);
		};
	}
}