#pragma once
#include "../components/viewport.h"

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
			RECT_COLLIDER,
			CHARACTER_CONTROLLER_2D
		};

		class GameObject;
		class IComponent
		{
		friend class GameObject;
		protected:
			virtual ~IComponent() = 0;
			IComponent(const COMPONENT_TYPE a_ComponentType, GameObject& a_GameObj, bool a_bIsEnabled = true);

			static bool isComponentOfTypeExistInGameObj(COMPONENT_TYPE a_ComponentType, const GameObject* a_pGameObject);

			bool m_bIsEnabled = true;

			virtual void onEnable();
			virtual void onDisable();

			void onGameObjectActivated(bool a_bIsGameObjectActivated);

		public:
			IComponent() = delete;

			const COMPONENT_TYPE m_ComponentType;
			GameObject& m_GameObject;

			virtual void update(float a_fDeltaTime) {};
			virtual void render(const glm::mat4& a_mat4Transformation, const Viewport& a_Camera) {};
			virtual void debugRender(const glm::mat4& a_mat4Transformation, const Viewport& a_Camera) {};

			void setIsEnabled(bool a_bIsEnabled);
			bool isEnabled() const;
			bool isActiveAndEnabled() const;
		};
	}
}