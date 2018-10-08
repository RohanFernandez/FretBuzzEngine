#pragma once

#include "../../system/component.h"
#include <string>
#include "../../graphics/shader.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class GameObject;
		class Light : public ns_system::IComponent
		{
		public:
			enum class LIGHT_TYPE
			{
				DIRECTIONAL,
				POINT,
				SPOT
			};

			struct LightSource
			{
				static constexpr char UNIF_LIGHT_POSITION[] = "u_Light.u_v4LightPosition";
				glm::vec4 m_v4LightPosition; // If m_v4LightVector.w == 0.0f then its directional else its positional

				static constexpr char UNIF_LIGHT_DIRECTION[] = "u_Light.u_v3LightDirection";
				glm::vec3 m_v3LightDirection;

				static constexpr char UNIF_CONST_LIN_QUAD[] = "u_Light.u_v3ConstLinQuad";
				glm::vec3 m_v3ConstLinQuad;

				// Light color
				static constexpr char UNIF_AMBIENT_COLOR[] = "u_Light.u_v3AmbientColor";
				glm::vec3 m_v3AmbientColor;

				static constexpr char UNIF_DIFFUSE_COLOR[] = "u_Light.u_v3DiffuseColor";
				glm::vec3 m_v3Diffuse;

				static constexpr char UNIF_SPECULAR_COLOR[] = "u_Light.u_v3SpecularColor";
				glm::vec3 m_v3Specular;

				//SpotLight specific
				static constexpr char UNIF_INNER_CUT_OFF[] = "u_Light.u_fInnerCutOff";
				float m_fInnerCutOff;

				static constexpr char UNIF_OUTER_CUT_OFF[] = "u_Light.u_fOuterCutOff";
				float m_fOuterCutOff;
			};

		protected:
			LIGHT_TYPE m_LightType;

			Light(ns_system::GameObject& a_GameObj, LIGHT_TYPE a_LightType);
			virtual ~Light();

		public:
			static Light* addToGameObject(ns_system::GameObject& a_GameObj, LIGHT_TYPE a_LightType);

			void updateUniforms(Shader& a_Shader);

			LightSource m_LightSource;

			LIGHT_TYPE getType() const;
			void setType(LIGHT_TYPE a_LIGHT_TYPE);

			virtual void update(float a_fDeltaTime) override;
		};
	}
}