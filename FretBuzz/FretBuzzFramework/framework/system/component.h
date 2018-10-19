#pragma once
#include "../components/viewport.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Camera;
	}

	namespace ns_system
	{
		enum class COMPONENT_TYPE
		{
			AUDIO_SOURCE,
			SPRITE_RENDERER,
			SPRITE_ANIMATION_CONTROLLER,
			TEXT_RENDERER,
			CHARACTER_CONTROLLER_2D,
			CAMERA,
			MESH_FILTER,
			MESH_RENDERER,
			LIGHT,

			//2D GameObject specific
			IMAGE,
			RECT_COLLIDER,

			//Custom user created
			BEHAVIOUR
		};

		class GameObject;
		class IComponent
		{
		friend class GameObject;

		protected:
			bool m_bIsEnabled = true;
			virtual ~IComponent() = 0;
			IComponent(const COMPONENT_TYPE a_ComponentType, GameObject& a_GameObj, bool a_bIsEnabled = true);

			// Does the component of type m_ComponentType exists in the GameObject m_Components list.
			static bool isComponentOfTypeExistInGameObj(COMPONENT_TYPE a_ComponentType, const GameObject* a_pGameObject);

			// Event called when the GameObject is activated.
			virtual void onEnable();

			// Event called when the GameObject is deactivated.
			virtual void onDisable();

			// Called when the GameBoject is activated or deactivated
			// Calls the onEnable / onDisable callback if the component is enabled / disabled respectively.
			void onGameObjectActivated(bool a_bIsGameObjectActivated);

		public:
			IComponent() = delete;

			const COMPONENT_TYPE m_ComponentType;
			GameObject& m_GameObject;

			// Called once per frame.
			virtual void update(float a_fDeltaTime) {};

			// Called once per frame to render the component if any renderables exist.
			virtual void render(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera) {};

			// Called if the _IS_DEBUG or _IS_DEBUG_RENDERING is defined.
			// Called once per frame to render the component if any debug renderables exist.
			virtual void debugRender(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera) {};

			// Enables/Disables the component.
			// Calls the onEnable/ onDisable event if the GameObject is active.
			void setIsEnabled(bool a_bIsEnabled);

			//Is the component enabled, does not depend if the GameObject is activated/deactivated.
			bool getIsEnabled() const;

			//Is the component enabled and the GameObject activated.
			bool isActiveAndEnabled() const;
		};
	}
}