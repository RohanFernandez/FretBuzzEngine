#include <fretbuzz_pch.h>
#include "canvas.h"
#include <system/camera_manager.h>

namespace FRETBUZZ
{
	Canvas::Canvas(GameObject2D* a_GameObject2D, CanvasData& a_CanvasData, bool a_bIsEnabled)
		: IComponent2D(COMPONENT_TYPE::CANVAS, a_GameObject2D, a_bIsEnabled)
	{
		setupCanvas(a_CanvasData);
	}

	Canvas::~Canvas()
	{
		
	}

	void Canvas::setupCanvas(CanvasData& a_CanvasData)
	{
		m_CanvasType = a_CanvasData.m_CanvasSpaceType;

		//Setup the camera type
		Camera* l_pCamera = nullptr;
		if ((m_CanvasType != CANVAS_SPACE_TYPE::WORLD_SPACE) && (a_CanvasData.m_pCamera == nullptr))
		{
			l_pCamera = &CameraManager::getMainCamera();
		}
		else
		{
			l_pCamera = a_CanvasData.m_pCamera;
		}
		m_pCamera = l_pCamera;

		//Setup plane distance
		m_fPlaneDistance = (m_CanvasType == CANVAS_SPACE_TYPE::SCREEN_SPACE_OVERLAY) ? 0.0f : a_CanvasData.m_fPlaneDistance;
	}

	//If the canvas is not world space, then it sets the canvas gameobject to be projected in front of the given camera,
	// The canvas's local position then works as if its center is at the center of the camera
	void Canvas::lateUpdate(const float& a_fDeltaTime)
	{
		if (m_CanvasType != CANVAS_SPACE_TYPE::WORLD_SPACE)
		{
			if (m_CanvasType == CANVAS_SPACE_TYPE::SCREEN_SPACE_OVERLAY)
			{
				m_GameObject.m_Transform.setWorldPosition(m_pCamera->m_GameObject.m_Transform.getWorldPosition() + (m_pCamera->m_GameObject.m_Transform.getForward() * m_pCamera->getViewport().getNearFar().x));
			}
			else if (m_CanvasType == CANVAS_SPACE_TYPE::SCREEN_SPACE_CAMERA)
			{
				m_GameObject.m_Transform.setWorldPosition(m_pCamera->m_GameObject.m_Transform.getWorldPosition() + (m_pCamera->m_GameObject.m_Transform.getForward() * m_fPlaneDistance));
			}

			//m_GameObject.m_Transform.setLocalRotation(m_pCamera->m_GameObject.m_Transform.getLocalRotation());
		}
	}
}