#pragma once
#include "../components/camera/camera.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		enum COMPONENT_TYPE
		{
			TRANSFORM,
			AUDIO_SOURCE
		};

		class IComponent
		{
		public:
			const COMPONENT_TYPE m_ComponentType;

			IComponent(COMPONENT_TYPE a_ComponentType)
				: m_ComponentType{ a_ComponentType }
			{};

			virtual ~IComponent() = 0
			{
			}

			virtual void update(float a_fDeltaTime)
			{
			
			}

			virtual void render(const Camera& a_Camera)
			{
			
			}
		};
	}
}