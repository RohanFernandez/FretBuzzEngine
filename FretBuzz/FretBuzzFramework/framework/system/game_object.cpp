#include <fretbuzz_pch.h>
#include "system/system_defines.h"
#include "game_object.h"
#include "components/gameobject_components/camera.h"
#include <imgui/imgui.h>
#include "core/layer/layer_mask.h"
#include <system/editor/editor_inspector.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//static counter that specifies the id.
		int GameObject::s_iID = 0;

		//GameObject 2D constructor
		GameObject::GameObject(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, Transform* a_pTransform, Layer a_Layer, bool a_bIsActiveSelf)
			: m_iID{ ++s_iID },
			m_strID{ std::to_string(m_iID) },
			m_strName{ a_strName },
			m_bIsActiveSelf{ a_bIsActiveSelf },
			m_bIsActiveInHierarchy{ !a_ParentGameObject.m_bIsActiveInHierarchy },
			m_pTransform{ a_pTransform },
			m_Transform(*a_pTransform),
			m_Layer {a_Layer}
		{
			a_ParentGameObject.addChild(this);
		}

		GameObject::GameObject(std::string a_strName, bool a_bIsRoot)
			: m_iID{++s_iID},
			m_strID{ std::to_string(m_iID) },
		    m_strName{a_strName},
			m_bIsRoot{a_bIsRoot},
			m_pTransform{ new Transform() },
			m_Transform(*m_pTransform)
		{
		}

		GameObject::GameObject(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, Layer a_Layer, bool a_bIsActiveSelf)
			: m_iID{ ++s_iID },
			m_strID{ std::to_string(m_iID) },
			m_strName{ a_strName },
			m_bIsActiveSelf{ a_bIsActiveSelf },
			m_bIsActiveInHierarchy{ !a_ParentGameObject.m_bIsActiveInHierarchy },
			m_pTransform{ new Transform(a_v3Position, a_v3Rotation, a_v3Scale, a_ParentGameObject.m_pTransform) },
			m_Transform(*m_pTransform),
			m_Layer{ a_Layer }
		{
			a_ParentGameObject.addChild(this);
		}

		GameObject::GameObject(GameObject& a_ParentGameObject, std::string a_strName, Layer a_Layer, bool a_bIsActiveSelf)
			: GameObject(a_ParentGameObject, a_strName, {0.0f, 0.0f,0.0f}, { 0.0f, 0.0f,0.0f }, { 1.0f, 1.0f,1.0f }, a_Layer, a_bIsActiveSelf)
		{
		}

		GameObject::~GameObject()
		{
			for (std::vector<GameObject*>::iterator l_IGameObjCurrent = m_Children.begin();
				l_IGameObjCurrent != m_Children.end();)
			{
				delete (*l_IGameObjCurrent);
				l_IGameObjCurrent = m_Children.erase(l_IGameObjCurrent);
			}

			for (std::vector<IComponent*>::iterator l_IComponentCurrent = m_Components.begin();
				l_IComponentCurrent != m_Components.end();)
			{
				delete (*l_IComponentCurrent);
				l_IComponentCurrent = m_Components.erase(l_IComponentCurrent);
			}

			if (m_pTransform != nullptr)
			{
				delete m_pTransform;
				m_pTransform = nullptr;
			}


		}

		GameObject* GameObject::instantiate(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, Layer a_Layer, bool a_bIsActiveSelf)
		{
			return new GameObject(a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_Layer, a_bIsActiveSelf);
		}

		GameObject* GameObject::instantiate(GameObject& a_ParentGameObject, std::string a_strName, Layer a_Layer, bool a_bIsActiveSelf)
		{
			return new GameObject(a_ParentGameObject, a_strName, {0.0f,0.0f,0.0f}, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, a_Layer, a_bIsActiveSelf);
		}

		void GameObject::addChild(GameObject* a_pChildGameObject)
		{
			a_pChildGameObject->setAsParent(this);
		}

		void GameObject::addComponent(IComponent* a_IComponent)
		{
			m_Components.emplace_back(a_IComponent);
		}

		void GameObject::update(float a_fDeltaTime)
		{
			updateComponents(a_fDeltaTime);
			updateChildren(a_fDeltaTime);
		}

		void GameObject::updateComponents(float a_fDeltaTime)
		{
			for (int l_iComponentndex = 0; l_iComponentndex < m_Components.size(); l_iComponentndex++)
			{
				if (m_Components[l_iComponentndex]->getIsEnabled())
				{
					m_Components[l_iComponentndex]->update(a_fDeltaTime);
				}
			}
		}

		void GameObject::lateUpdateChildren(float a_fDeltaTime)
		{
			GameObject* l_pCurrentGameObject = nullptr;

			for (int l_iChildIndex = 0; l_iChildIndex < m_Children.size(); l_iChildIndex++)
			{
				l_pCurrentGameObject = m_Children[l_iChildIndex];
				if (l_pCurrentGameObject->getIsActiveInHierarchy())
				{
					l_pCurrentGameObject->update(a_fDeltaTime);
				}
			}
		}

		void GameObject::lateUpdate(float a_fDeltaTime)
		{
			lateUpdateComponents(a_fDeltaTime);
			lateUpdateChildren(a_fDeltaTime);
		}

		void GameObject::updateChildren(float a_fDeltaTime)
		{
			GameObject* l_pCurrentGameObject = nullptr;

			for (int l_iChildIndex = 0; l_iChildIndex < m_Children.size(); l_iChildIndex++)
			{
				l_pCurrentGameObject = m_Children[l_iChildIndex];
				if (l_pCurrentGameObject->getIsActiveInHierarchy())
				{
					l_pCurrentGameObject->lateUpdate(a_fDeltaTime);
				}
			}
		}

		void GameObject::lateUpdateComponents(float a_fDeltaTime)
		{
			for (int l_iComponentndex = 0; l_iComponentndex < m_Components.size(); l_iComponentndex++)
			{
				if (m_Components[l_iComponentndex]->getIsEnabled())
				{
					m_Components[l_iComponentndex]->lateUpdate(a_fDeltaTime);
				}
			}
		}

		void GameObject::editorHierarchyRender(GameObject*& a_pSelectedGameObject)
		{
			int l_iChildrenCount = m_Children.size();

			const auto m_NodeFlags = ImGuiTreeNodeFlags_OpenOnArrow
				| (l_iChildrenCount == 0 ? ImGuiTreeNodeFlags_Leaf : 0)
				| (((a_pSelectedGameObject != nullptr) && (a_pSelectedGameObject->m_iID == m_iID)) ? ImGuiTreeNodeFlags_Selected : 0);

			bool l_bIsTreeNodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)m_iID, m_NodeFlags, m_strName.c_str());
			if (ImGui::IsItemClicked())
			{
				a_pSelectedGameObject = this;
			}

			if (l_bIsTreeNodeOpen)
			{
				for (int l_iChildIndex = 0; l_iChildIndex < l_iChildrenCount; l_iChildIndex++)
				{
					m_Children[l_iChildIndex]->editorHierarchyRender(a_pSelectedGameObject);
				}
				ImGui::TreePop();
			}
		}

		void GameObject::render(const ns_graphics::Camera& a_Camera)
		{
			if (getIsActiveInHierarchy() && a_Camera.m_CullingMask.isLayerInMask(m_Layer))
			{
				const glm::mat4 l_mat4RenderTransformation = a_Camera.getProjectionMatrix() * a_Camera.getViewMatrix() * m_pTransform->getTransformationMatrix();
				renderComponents(l_mat4RenderTransformation, a_Camera);
			}
			renderChildren(a_Camera);
		}

		void GameObject::renderComponents(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera)
		{
			int l_iComponentCount = m_Components.size();
			for (int l_iComponentndex = 0; l_iComponentndex < l_iComponentCount; l_iComponentndex++)
			{
				IComponent& l_Component =  *m_Components[l_iComponentndex];

				if (l_Component.getIsEnabled())
				{
					l_Component.render(a_mat4Transformation, a_Camera);

#ifdef _IS_DEBUG_RENDERING
					l_Component.debugRender(a_mat4Transformation, a_Camera);
#endif
				}
			}
		}

		void GameObject::renderChildren(const ns_graphics::Camera& a_Camera)
		{
			GameObject* l_pCurrentGameObject = nullptr;

			int l_iChildCount = m_Children.size();
			for (int l_iChildIndex = 0; l_iChildIndex < l_iChildCount; l_iChildIndex++)
			{
				l_pCurrentGameObject = m_Children[l_iChildIndex];
				if (l_pCurrentGameObject->getIsActiveInHierarchy())
				{
					l_pCurrentGameObject->render(a_Camera);
				}
			}
		}

		bool GameObject::isComponentTypeExist(COMPONENT_TYPE a_ComponentType) const
		{
			int l_iComponentCount = m_Components.size();
			for (int l_iComponentIndex = 0; l_iComponentIndex < l_iComponentCount; l_iComponentIndex++)
			{
				if (m_Components[l_iComponentIndex]->m_ComponentType == a_ComponentType)
				{
					return true;
				}
			}
			return false;
		}

		void GameObject::resetDontDestroyParent(GameObject& a_NewParent)
		{
			for (std::vector<GameObject*>::iterator l_IChildObjCurrent = m_Children.begin();
				l_IChildObjCurrent != m_Children.end();)
			{
				GameObject& l_ChildGameObj = **l_IChildObjCurrent;

				if (l_ChildGameObj.isDontDestroy())
				{
					a_NewParent.addChild(&l_ChildGameObj);
					l_IChildObjCurrent = m_Children.erase(l_IChildObjCurrent);
				}
				else
				{
					l_ChildGameObj.resetDontDestroyParent(a_NewParent);
					l_IChildObjCurrent++;
				}
			}
		}

		void GameObject::setAsParent(GameObject* a_pNewParentGameObject)
		{
			if (m_bIsRoot)
			{
				std::cout << "GameObject::setAsParent:: A gameobject  name::[" << a_pNewParentGameObject->getName() << "]  cannot be set as the parent of a ROOT GameObject name::[" << getName() << "]\n";
				return;
			}

			if (a_pNewParentGameObject == this || a_pNewParentGameObject == m_pParentGameObject)
			{
				//std::cout << "GameObject::setAsParent:: The new parent to set of the child GameObject are the same GameObject\n";
				return;
			}

			if (m_pParentGameObject != nullptr)
			{
				std::vector<GameObject*>& m_CurrentParentsChildren = m_pParentGameObject->m_Children;

				for (std::vector<GameObject*>::iterator l_Iterator = m_CurrentParentsChildren.begin();
					l_Iterator != m_CurrentParentsChildren.end();
					l_Iterator++)
				{
					if (*l_Iterator == this)
					{
						m_CurrentParentsChildren.erase(l_Iterator);
						break;
					}
				}
			}
			m_pParentGameObject = a_pNewParentGameObject;
			m_pParentGameObject->m_Children.emplace_back(this);
			m_pTransform->m_pParentTransform = m_pParentGameObject->m_pTransform;

			setActive(m_bIsActiveSelf);

			//TODO :: Add on parent change callback to change transformations
		}

		void GameObject::logHierarchy(int l_iNumOfTabs)
		{
			std::string l_strLog = "\n";

			for (int l_iTabIndex = 0; l_iTabIndex < l_iNumOfTabs; l_iTabIndex++)
			{
				l_strLog += "\t";
			}
			l_strLog += "=> " + m_strName;

			if (!getIsActiveInHierarchy())
			{
				l_strLog += " [DISABLED]";
			}
			if (m_bIsDontDestroy)
			{
				l_strLog += " [DONT_DESTROY]";
			}

			std::cout << l_strLog;

			++l_iNumOfTabs;
			for (std::vector<GameObject*>::iterator l_IChildObjCurrent = m_Children.begin();
				l_IChildObjCurrent != m_Children.end(); l_IChildObjCurrent++)
			{
				(*l_IChildObjCurrent)->logHierarchy(l_iNumOfTabs);
			}
		}

		bool GameObject::getIsActiveSelf() const
		{
			return m_bIsActiveSelf;
		}

		bool GameObject::getIsActiveInHierarchy() const
		{
			return m_bIsActiveInHierarchy;
		}

		void GameObject::setActive(bool a_bIsActiveSelf)
		{
			if (m_pParentGameObject == nullptr)
			{
				return;
			}

			bool l_bIsActiveInHierarchyOld = m_bIsActiveInHierarchy;
			m_bIsActiveSelf = a_bIsActiveSelf;
			m_bIsActiveInHierarchy = m_pParentGameObject->getIsActiveInHierarchy() && m_bIsActiveSelf;

			if (l_bIsActiveInHierarchyOld != m_bIsActiveInHierarchy)
			{
				setActiveInHierarchyRecursively(m_bIsActiveInHierarchy);
			}
		}

		void GameObject::setActiveInHierarchyRecursively(bool a_bIsActiveInHierarchy)
		{
			int l_iComponentCount = m_Components.size();
			for (int l_iComponentIndex = 0; l_iComponentIndex < l_iComponentCount; l_iComponentIndex++)
			{
				m_Components[l_iComponentIndex]->onGameObjectActivated(a_bIsActiveInHierarchy);
			}

			int l_iChildCount = m_Children.size();
			for (int l_iChildIndex = 0; l_iChildIndex < l_iChildCount; l_iChildIndex++)
			{
				GameObject& l_Child = *m_Children[l_iChildIndex];

				if (l_Child.getIsActiveSelf())
				{
					l_Child.m_bIsActiveInHierarchy = a_bIsActiveInHierarchy;
					l_Child.setActiveInHierarchyRecursively(a_bIsActiveInHierarchy);
				}
			}
		}

		std::string GameObject::getName() const
		{
			return m_strName;
		}

		GameObject* GameObject::setAsDontDestroy(bool a_bIsDontDestroy)
		{
			m_bIsDontDestroy = a_bIsDontDestroy;
			return this;
		}

		bool GameObject::isDontDestroy() const
		{
			return m_bIsDontDestroy;
		}

		void GameObject::destroy(GameObject*& a_pGameObject)
		{
			if (a_pGameObject == nullptr)
			{
				std::cout << "GameObject::destroy:: GameObject to destroy is null\n";
				return;
			}

			std::vector<GameObject*>& l_vectChildren = a_pGameObject->m_pParentGameObject->m_Children;
			for (std::vector<GameObject*>::iterator l_Iterator = l_vectChildren.begin(),
				l_IteratorEnd = l_vectChildren.end();
				l_Iterator != l_IteratorEnd;
				l_Iterator++)
			{
				if (*l_Iterator == a_pGameObject)
				{
					l_Iterator = l_vectChildren.erase(l_Iterator);
					delete a_pGameObject;
					a_pGameObject = nullptr;
					return;
				}
			}

			std::cout << "GameObject::destroy:: GameObject to destroy with name :: " << a_pGameObject->getName() << 
				" and ID :: " << a_pGameObject->m_iID << " was not found in the Parent's children\n";
		}


		void GameObject::editorTransformRender()
		{
			
		}
	}
}