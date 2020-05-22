#pragma once

#include "system/component.h"
#include "graphics/shader.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class GameObject;
		class  Light : public ns_system::IComponent
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
				static constexpr char UNIF_DIRECTIONAL_LIGHT[] = "u_DirectionalLight["; 
				static constexpr char UNIF_POINT_LIGHT[] = "u_PointLight[";
				static constexpr char UNIF_SPOT_LIGHT[] = "u_SpotLight[";

				static constexpr char UNIF_LIGHT_POSITION[] = "].u_v4LightPosition";
				glm::vec4 m_v4LightPosition; // If m_v3LightVector.w == 0.0f then its directional else its positional

				static constexpr char UNIF_LIGHT_DIRECTION[] = "].u_v3LightDirection";
				glm::vec3 m_v3LightDirection;

				static constexpr char UNIF_CONST_LIN_QUAD[] = "].u_v3ConstLinQuad";
				glm::vec3 m_v3ConstLinQuad;

				// Light color
				static constexpr char UNIF_AMBIENT_COLOR[] = "].u_v3AmbientColor";
				glm::vec3 m_v3AmbientColor = {0.0f, 0.0f, 0.0f};

				static constexpr char UNIF_DIFFUSE_COLOR[] = "].u_v3DiffuseColor";
				glm::vec3 m_v3Diffuse = { 0.0f, 0.0f, 0.0f };

				static constexpr char UNIF_SPECULAR_COLOR[] = "].u_v3SpecularColor";
				glm::vec3 m_v3Specular = { 0.0f, 0.0f, 0.0f };

				//SpotLight specific
				static constexpr char UNIF_INNER_CUT_OFF[] = "].u_fInnerCutOff";
				float m_fInnerCutOff = glm::cos(glm::radians(12.0f));

				static constexpr char UNIF_OUTER_CUT_OFF[] = "].u_fOuterCutOff";
				float m_fOuterCutOff = glm::cos(glm::radians(25.0f));

				static constexpr char UNIF_INTENSITY[] = "].u_fIntensity";
				float m_fIntensity = 1.0f;

				static constexpr char UNIF_DIR_LIGHT_COUNT[] = "u_iDirectionalLightCount";
				static constexpr char UNIF_POINT_LIGHT_COUNT[] = "u_iPointLightCount";
				static constexpr char UNIF_SPOT_LIGHT_COUNT[] = "u_iSpotLightCount";

				inline void setOuterCutOff(float a_fAngleInDegrees)
				{
					m_fInnerCutOff = glm::cos(glm::radians(a_fAngleInDegrees));
				}

				inline void setInnerCutOff(float a_fAngleInDegrees)
				{
					m_fOuterCutOff = glm::cos(glm::radians(a_fAngleInDegrees));
				}
			};

		protected:
			LIGHT_TYPE m_LightType;

			virtual ~Light();

		public:
			Light(ns_system::GameObject* a_GameObj, LIGHT_TYPE a_LightType);
			static Light* addToGameObject(ns_system::GameObject& a_GameObj, LIGHT_TYPE a_LightType);

			LightSource m_LightSource;

			LIGHT_TYPE getType() const;
			void setType(LIGHT_TYPE a_LIGHT_TYPE);

			virtual void update(float a_fDeltaTime) override;
		};
	}
}