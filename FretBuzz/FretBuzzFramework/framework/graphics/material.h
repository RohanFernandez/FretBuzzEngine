#pragma once
#include "shader.h"
#include "texture.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Material
		{
		public:

			struct MaterialData
			{
				static constexpr char UNIF_MAT_SHININESS[] = "u_Material.u_fShininess";
				float m_fShininess = 32.0f;

				static constexpr char UNIF_MAT_TEX_DIFFUSE[] = "u_Material.u_texDiffuse";
				Texture* m_pTexDiffuse = nullptr;

				static constexpr char UNIF_MAT_TEX_SPECULAR[] = "u_Material.u_texSpecular";
				Texture* m_pTexSpecular = nullptr;
			};

			Material();
			~Material();

			Shader* m_pShader = nullptr;
			MaterialData m_MaterialData;

			void setShader(Shader& a_pShader);
			Shader* getShader();

			void updateUniform();
		};
	}
}