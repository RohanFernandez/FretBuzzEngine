#pragma once

namespace FRETBUZZ
{
	class Material;
	class Camera;
	class Shader;

	class  DefaultLineShader : Shader
	{
	private:
		static DefaultLineShader* s_pInstance;

		DefaultLineShader(std::string a_strShaderName);
		virtual ~DefaultLineShader();

	public:
		static DefaultLineShader* initialize(std::string a_strShaderPath);
		virtual void bind(const Material& a_Material, const Camera& a_Camera) const override;
		virtual void destroy() override;
	};
}