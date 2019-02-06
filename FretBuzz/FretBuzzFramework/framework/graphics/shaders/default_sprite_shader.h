#pragma once

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Material;
		class Camera;
		class Shader;

		class FRETBUZZ_API DefaultSpriteShader : Shader
		{
		private:
			static DefaultSpriteShader* s_pInstance;

			DefaultSpriteShader(std::string a_strShaderName);
			virtual ~DefaultSpriteShader();

		public:
			static DefaultSpriteShader* initialize(std::string a_strShaderPath);
			virtual void bind(const Material& a_Material, const Camera& a_Camera) const override;
			virtual void destroy() override;
		};
	}
}