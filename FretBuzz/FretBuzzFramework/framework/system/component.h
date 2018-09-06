#pragma once
#include "../components/camera.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		enum COMPONENT_TYPE
		{
			AUDIO_SOURCE,
			SPRITE_RENDERER,
			SPRITE_ANIMATION_CONTROLLER,
			TEXT_RENDERER,
			RECT_COLLIDER
		};

		class GameObject;
		class IComponent
		{
		friend class GameObject;
		protected:
			virtual ~IComponent() = 0 {}
			IComponent(const COMPONENT_TYPE a_ComponentType, GameObject& a_GameObj);

			static bool isComponentOfTypeExistInGameObj(COMPONENT_TYPE a_ComponentType, const GameObject* a_pGameObject);

		public:
			IComponent() = delete;

			const COMPONENT_TYPE m_ComponentType;
			GameObject& m_GameObject;

			virtual void update(float a_fDeltaTime);
			virtual void render(const glm::mat4& a_mat4Transformation, const Camera& a_Camera);
		};
	}
}