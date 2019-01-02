#pragma once

#include "camera.h"
#include "../viewport.h"
#include "system/game_object.h"
#include "system/camera_manager.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Camera::Camera(ns_system::GameObject& a_GameObj, Viewport::PROJECTION_TYPE a_ProjectionType, Viewport* a_Viewport)
			: IComponent(ns_system::COMPONENT_TYPE::CAMERA, a_GameObj),
			m_PROJECTION_TYPE(a_ProjectionType)
		{
			if (a_ProjectionType == Viewport::PROJECTION_TYPE::ORTHOGRAPHIC)
			{
				OrthographicViewport* l_pOrthoViewport = dynamic_cast<OrthographicViewport*>(a_Viewport);
				m_pViewPort = new OrthographicViewport(*l_pOrthoViewport);
			}
			else
			{
				PerspectiveViewport* l_pPerspectiveViewport = dynamic_cast<PerspectiveViewport*>(a_Viewport);
				m_pViewPort = new PerspectiveViewport(*l_pPerspectiveViewport);
			}
			
			CameraManager::s_registerCamera(this);
		}

		Camera::~Camera()
		{
			CameraManager::s_unregisterCamera(this);
			if (m_pViewPort != nullptr)
			{
				delete m_pViewPort;
				m_pViewPort = nullptr;
			}
		}

		Viewport& Camera::getViewport()
		{
			return *m_pViewPort;
		}

		Viewport::PROJECTION_TYPE Camera::getProjectionType() const
		{
			return m_PROJECTION_TYPE;
		}

		Camera* Camera::addToGameObject(ns_system::GameObject& a_GameObj, Viewport::PROJECTION_TYPE a_ProjectionType, Viewport* a_pViewport)
		{
			return IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::CAMERA, &a_GameObj) ?
				nullptr : new Camera(a_GameObj, a_ProjectionType, a_pViewport);
		}

		const glm::mat4 Camera::getViewMatrix() const
		{
			return m_mat4View;
		}

		const glm::mat4 Camera::updateViewMatrix()
		{
			glm::vec3 l_v3WorldPosition = m_GameObject.m_Transform.getWorldPosition();
			m_mat4View = glm::lookAt(l_v3WorldPosition, l_v3WorldPosition + m_GameObject.m_Transform.getForward(), m_GameObject.m_Transform.getUp());
			return m_mat4View;
		}

		const glm::mat4 Camera::getProjectionMatrix() const
		{
			return m_pViewPort->getProjectionMatrix();
		}

		void Camera::reset()
		{
			m_pViewPort->resetProjectionMatrix();
		}

		void Camera::zoom(float a_fFactor)
		{
			if (m_PROJECTION_TYPE == Viewport::PROJECTION_TYPE::ORTHOGRAPHIC)
			{
				OrthographicViewport* l_pOrthoViewport = dynamic_cast<OrthographicViewport*>(m_pViewPort);
				glm::vec2 l_v2LeftRight = l_pOrthoViewport->getLeftRight();
				glm::vec2 l_v2BottomTop = l_pOrthoViewport->getBottomTop();
				glm::vec2 l_v2NearFar = l_pOrthoViewport->getNearFar();

				l_pOrthoViewport->setProjectionMatrix(l_v2LeftRight.x + a_fFactor, l_v2LeftRight.y - a_fFactor, l_v2BottomTop.x + a_fFactor, l_v2BottomTop.y - a_fFactor, l_v2NearFar.x, l_v2NearFar.y);
			}
			else
			{
				PerspectiveViewport* l_pPerspectiveViewport = dynamic_cast<PerspectiveViewport*>(m_pViewPort);
				float a_fAspectRatio = l_pPerspectiveViewport->getAspectRatio();
				glm::vec2 l_v2NearFar = l_pPerspectiveViewport->getNearFar();
				float l_fFOV = l_pPerspectiveViewport->getFOV();

				l_pPerspectiveViewport->setProjectionMatrix(l_fFOV - a_fFactor, a_fAspectRatio, l_v2NearFar.x, l_v2NearFar.y);
			}
		}
	}
}