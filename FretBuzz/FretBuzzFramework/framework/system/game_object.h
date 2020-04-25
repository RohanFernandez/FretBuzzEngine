#pragma once

#include "components/transform.h"
#include "components/gameobject_components/camera.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class FRETBUZZ_API GameObject
		{
			friend class IScene;
			friend class IComponent;
			
		protected:

			std::vector<IComponent*> m_Components;
			std::vector<GameObject*> m_Children;
			bool m_bIsRoot = false;

			GameObject* m_pParentGameObject = nullptr;

			const std::string m_strName;

			// The int ID of the current gameobject
			const int m_iID;

			const std::string m_strID;

			// The total number of gameobjects, provides a unique ID for nw gameobjects.
			static int s_iID;

			bool m_bIsDontDestroy = false;

			bool m_bIsActiveSelf = true;
			bool m_bIsActiveInHierarchy = true;

			void setActiveInHierarchyRecursively(bool a_bIsActive);

			void updateComponents(float a_fDeltaTime);
			void updateChildren(float a_fDeltaTime);

			void lateUpdateComponents(float a_fDeltaTime);
			void lateUpdateChildren(float a_fDeltaTime);

			void renderComponents(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera);
			void renderChildren(const ns_graphics::Camera& a_Camera);

			// Renders all the inspector hierarchy data.
			virtual void editorHierarchyRender(GameObject*& a_pSelectedGameObject);
			
			void addComponent(IComponent* a_IComponent);
			void resetDontDestroyParent(GameObject& a_NewParent);
			glm::mat4 m_mat4Transformation{1.0f};

			GameObject(std::string a_strName, bool a_bIsRoot = true);
			GameObject(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, Layer a_Layer, bool a_bIsActiveSelf = true);
			GameObject(GameObject& a_ParentGameObject, std::string a_strName, Layer a_Layer, bool a_bIsActiveSelf);

			// GameObject 2D constructor
			GameObject(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, Transform* a_pTransform, Layer a_Layer, bool a_bIsActiveSelf);

			Transform* m_pTransform;
			virtual ~GameObject();

		public:
			Layer m_Layer;

			// Creates a GameObject, adds this GameObject to the m_Children of its a_ParentGameObject.
			// Sets its active state in hierarchy to the a_bIsActiveSelf, depends on its ParentGameObject.
			static GameObject* instantiate(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, Layer a_Layer, bool a_bIsActiveSelf = true);
			static GameObject* instantiate(GameObject& a_ParentGameObject, std::string a_strName, Layer a_Layer, bool a_bIsActiveSelf = true);

			Transform& m_Transform;

			// Adds the GameObject a_pChildGameObject into this GameObject's m_Children.
			void addChild(GameObject* a_pChildGameObject);

			// Renders all the components and renders its child GameObjects.
			virtual void render(const ns_graphics::Camera& a_Camera);

			// Updates all the components and renders its child GameObjects.
			virtual void update(float a_fDeltaTime);

			// called after update on all the gameobjects are done
			virtual void lateUpdate(float a_fDeltaTime);

			// Does the component of type a_ComponentType exist in the m_Components list.
			bool isComponentTypeExist(COMPONENT_TYPE a_ComponentType) const;

			// Removes this GameObject from the current parent's m_Children list.
			// Sets this GameObject as the child of the a_pParentGameObject.
			void setAsParent(GameObject* a_pParentGameObject);

			// Is the GameObject active locally, even though its not active in the scene.
			bool getIsActiveSelf() const;

			// Is the GameObject active in the scene.
			bool getIsActiveInHierarchy() const;

			// Sets the GameObject active self state,
			// If a_bIsActive = true, sets the active state to true in hierarchy if the parent is also active
			// Sets its child active in hierarchy state to true if previously false.
			// If a_bIsActive = false, sets the active state to false in hierarchy if the parent is true/false
			// Sets its child active in hierarchy state to false if previously true.
			void setActive(bool a_bIsActive);

			// Gets the name of the GameObject.
			std::string getName() const;

			// GameObject won't be destroyed on Scene change.
			GameObject* setAsDontDestroy(bool a_bIsDontDestroy = true);

			// Is the gameobject a DontDestroy type of Object.
			bool isDontDestroy() const;

			// Logs GameObject hierarchy.
			void logHierarchy(int l_iNumOfTabs);

			// Removes the GameObject from its parent m_Children container.
			// Destroys the GameObject
			static void destroy(GameObject*& a_GameObject);

#pragma region Editor
			virtual void editorTransformRender();
#pragma endregion Editor
			
			// Returns all component of the game object
			inline const std::vector<IComponent*> getAllComponents()
			{
				return m_Components;
			}

			// Returns a component from the components vector, if the COMPONENT_TYPE is equal to the input.
			// If the component pointer is found it returns the component cast to the type specified else returns null.
			template<typename T_COMPONENT_TYPE, typename = typename std::enable_if<std::is_base_of<IComponent, T_COMPONENT_TYPE>::value>::type>
			T_COMPONENT_TYPE* getComponent(COMPONENT_TYPE a_COMPONENT_TYPE)
			{
				int l_iComponentCount = m_Components.size();
				for(int l_iComponentIndex = 0; l_iComponentIndex < l_iComponentCount; l_iComponentIndex++)
				{
					if (m_Components[l_iComponentIndex]->m_ComponentType == a_COMPONENT_TYPE)
					{
						return dynamic_cast<T_COMPONENT_TYPE*>(m_Components[l_iComponentIndex]);
					}
				}
				return nullptr;
			}
		};
	}
}