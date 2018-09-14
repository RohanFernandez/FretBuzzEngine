#pragma once

#include "camera.h"
#include "../viewport.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		Camera::Camera(GameObject& a_GameObj, Viewport& a_Viewport)
			: IComponent(COMPONENT_TYPE::CAMERA, a_GameObj)
		{

		}

		Camera::~Camera()
		{
		
		}
	}
}