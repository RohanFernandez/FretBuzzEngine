#pragma once

namespace FRETBUZZ
{
	class Material;
	class Camera;
	class Shader;

	class  DefaultSpriteShader : Shader
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