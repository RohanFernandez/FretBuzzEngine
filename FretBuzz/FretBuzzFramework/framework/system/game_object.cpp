#pragma once
#include "../system/core/system_defines.h"
#include "game_object.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//static counter that specifies the id.
		int GameObject::s_iID = 0;

		GameObject::GameObject(std::string a_strName, bool a_bIsRoot)
			: m_iID{++s_iID},
		     m_strName{a_strName},
			 m_Transform(),
			m_bIsRoot{a_bIsRoot}
		{
			
		}

		GameObject::GameObject(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale)
			: m_iID{ ++s_iID },
			m_strName{ a_strName },
			m_Transform(a_v3Position, a_v3Rotation, a_v3Scale)
		{
			a_ParentGameObject.addChild(this);
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
		}

		GameObject* GameObject::instantiate(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale)
		{
			return new GameObject(a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale);
		}

		GameObject* GameObject::instantiate(GameObject& a_ParentGameObject, std::string a_strName)
		{
			return new GameObject(a_ParentGameObject, a_strName, {0.0f,0.0f,0.0f}, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f });
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
			int l_iComponentCount = m_Components.size();
			for (int l_iComponentndex = 0; l_iComponentndex < l_iComponentCount; l_iComponentndex++)
			{
				m_Components[l_iComponentndex]->update(a_fDeltaTime);
			}
		}

		void GameObject::updateChildren(float a_fDeltaTime)
		{
			int l_iChildCount = m_Children.size();
			GameObject* l_pCurrentGameObject = nullptr;

			for (int l_iChildIndex = 0; l_iChildIndex < l_iChildCount; l_iChildIndex++)
			{
				l_pCurrentGameObject = m_Children[l_iChildIndex];
				if (l_pCurrentGameObject->m_bIsActive)
				{
					l_pCurrentGameObject->update(a_fDeltaTime);
				}
			}
		}

		void GameObject::render(const glm::mat4& a_mat4Transformation, const Viewport& a_Camera)
		{
			m_mat4Transformation = a_mat4Transformation * m_Transform.getModelMatrix();
			glm::mat4 l_mat4RenderTransformation = a_Camera.getProjectionMatrix() * a_Camera.getViewMatrix() * m_mat4Transformation;

			renderComponents(l_mat4RenderTransformation, a_Camera);
			renderChildren(m_mat4Transformation, a_Camera);
		}

		void GameObject::renderComponents(const glm::mat4& a_mat4Transformation, const Viewport& a_Camera)
		{
			int l_iComponentCount = m_Components.size();
			for (int l_iComponentndex = 0; l_iComponentndex < l_iComponentCount; l_iComponentndex++)
			{
				m_Components[l_iComponentndex]->render(a_mat4Transformation, a_Camera);

#ifdef _IS_DEBUG_RENDERING
				m_Components[l_iComponentndex]->debugRender(a_mat4Transformation, a_Camera);
#endif
			}
		}

		void GameObject::renderChildren(const glm::mat4& a_mat4Transformation, const Viewport& a_Camera)
		{
			GameObject* l_pCurrentGameObject = nullptr;

			int l_iChildCount = m_Children.size();
			for (int l_iChildIndex = 0; l_iChildIndex < l_iChildCount; l_iChildIndex++)
			{
				l_pCurrentGameObject = m_Children[l_iChildIndex];

				if (l_pCurrentGameObject->isActive())
				{
					l_pCurrentGameObject->render(a_mat4Transformation, a_Camera);
				}
			}
		}

		void GameObject::setActive(bool a_bIsActive)
		{
			m_bIsActive = a_bIsActive;
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
				std::cout << "GameObject::setAsParent:: A gameobject  name::[" << a_pNewParentGameObject->getName()<< "]  cannot be set as the parent of a ROOT GameObject name::["<< getName()<<"]\n";
				return;
			}

			if (a_pNewParentGameObject == this)
			{
				std::cout << "GameObject::setAsParent:: The new parent to set of the child GameObject are the same GameObject\n";
				return;
			}

			if (m_pParentGameObject != nullptr)
			{
				std::vector<GameObject*> m_CurrentParentsChildren = m_pParentGameObject->m_Children;

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
		}

		void GameObject::logHierarchy(int l_iNumOfTabs)
		{
			std::string l_strLog = "\n";

			for (int l_iTabIndex = 0; l_iTabIndex < l_iNumOfTabs; l_iTabIndex++)
			{
				l_strLog += "\t";
			}
			l_strLog += "=> " + m_strName;
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
	}
}