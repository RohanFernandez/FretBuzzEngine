#pragma once

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Material;
		class Camera;
		class Shader;

		class FRETBUZZ_API Default3DShader : Shader
		{
		private:
			static Default3DShader* s_pInstance;

			Default3DShader(std::string a_strShaderName);
			virtual ~Default3DShader();

		public:
			static Default3DShader* initialize(std::string a_strShaderPath);
			virtual void bind(const Material& a_Material, const Camera& a_Camera) const override;
			virtual void destroy() override;
		};
	}
}