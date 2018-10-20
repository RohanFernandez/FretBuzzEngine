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
				glm::vec4 m_v4Albedo = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

				static constexpr char UNIF_MAT_TEX_DIFFUSE[] = "u_Material.u_fTexDiffuseIndex";
				Texture* m_pTexDiffuse = nullptr;

				static constexpr char UNIF_MAT_TEX_SPECULAR[] = "u_Material.u_fTexSpecularIndex";
				Texture* m_pTexSpecular = nullptr;

				
				static constexpr char UNIF_CAM_POSITION[] = "u_v3CamPosition";

				static constexpr int TOTAL_TEXTURE_SLOTS = 32;
				static constexpr GLint s_arrTextureIDArray[TOTAL_TEXTURE_SLOTS] =
				{
					0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
					17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
				};

				static constexpr char UNIFORM_TEXTURE_SAMPLER[] = "u_Material.u_arrTextureSampler";
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