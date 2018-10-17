#pragma once

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Material;
		class Camera;
		class Shader;

		class PhongShader : Shader
		{
		private:
			static PhongShader* s_pInstance;

			PhongShader(std::string a_strShaderName);
			virtual ~PhongShader();

		public:
			static PhongShader* initialize(std::string a_strShaderPath);
			virtual void bind(const Material& a_Material, const Camera& a_Camera) override;
			virtual void destroy() override;
		};
	}
}