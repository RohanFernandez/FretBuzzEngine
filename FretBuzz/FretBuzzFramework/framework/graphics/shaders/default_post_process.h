#pragma once

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Material;
		class Camera;
		class Shader;

		class DefaultPostProcess : Shader
		{
		private:
			static DefaultPostProcess* s_pInstance;

			DefaultPostProcess(std::string a_strShaderName);
			virtual ~DefaultPostProcess();

		public:
			static DefaultPostProcess* initialize(std::string a_strShaderPath);
			virtual void bind(const Material& a_Material, const Camera& a_Camera) const override;
			virtual void destroy() override;
		};
	}
}