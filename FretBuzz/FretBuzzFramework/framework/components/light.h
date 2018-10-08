#pragma once

#include "../system/component.h"

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

		protected:
			LIGHT_TYPE m_LightType;

			Light(ns_system::GameObject& a_GameObj, LIGHT_TYPE a_LightType);
			virtual ~Light();

			glm::vec4 m_Color = {1.0f, 1.0f, 1.0f, 1.0f};

		public:
			static Light* addToGameObject(ns_system::GameObject& a_GameObj, LIGHT_TYPE a_LightType);


		};
	}
}