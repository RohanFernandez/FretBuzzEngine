#pragma once
#include "../components/camera/camera.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		enum COMPONENT_TYPE
		{
			AUDIO_SOURCE,
			SPRITE_RENDERER,
			SPRITE_ANIMATOR
		};

		class GameObject;
		class IComponent
		{
		friend class GameObject;
		protected:
			virtual ~IComponent() = 0 {}
			IComponent(const COMPONENT_TYPE a_ComponentType, GameObject& a_GameObj);

		public:
			IComponent() = delete;

			const COMPONENT_TYPE m_ComponentType;
			GameObject& m_GameObject;

			virtual void update(float a_fDeltaTime);
			virtual void render(const Camera& a_Camera);
		};
	}
}