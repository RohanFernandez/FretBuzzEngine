#pragma once
#include "shader.h"
#include "texture.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Camera;
		class Material
		{
		public:

			struct MaterialData
			{
				static constexpr char UNIF_MAT_SHININESS[] = "u_Material.u_fShininess";
				float m_fShininess = 32.0f;

				static constexpr char UNIF_MAT_V4_ALBEDO[] = "u_Material.u_v4Albedo";
				glm::vec4 m_v4Albedo = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

				static constexpr char UNIF_MAT_TEX_DIFFUSE[] = "u_Material.u_texDiffuse";
				Texture* m_pTexDiffuse = nullptr;

				static constexpr char UNIF_MAT_TEX_SPECULAR[] = "u_Material.u_texSpecular";
				Texture* m_pTexSpecular = nullptr;

				static constexpr char UNIF_MAT_TEX_SAMPLER[] = "u_Material.u_fTexSampler";
				float m_arrTexSampler[32] = {};
				
				static constexpr char UNIF_CAM_POSITION[] = "u_v3CamPosition";
			};
			
			Material();
			~Material();

			Shader* m_pShader = nullptr;
			MaterialData m_MaterialData;

			void setShader(Shader& a_pShader);
			Shader* getShader();

			void bind(const Camera& a_Camera);
		};
	}
}