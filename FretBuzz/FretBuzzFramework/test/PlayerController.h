#pragma once

#include "../framework/utils/math.h"
#include "../framework/components/gameobject_components/camera.h"
#include "../framework/system/core/input.h"

#include "../framework/components/gameobject_components/behaviour.h"

namespace ns_fretBuzz
{
	class PlayerController : public ns_system::Behaviour
	{
	private:
		double m_MouseX, m_MouseY;
		bool m_bIsFirstRun = true;
		float m_fMouseSensitivity = 0.3f;

		glm::vec2 m_v2LastMouseXY;
		glm::vec2 m_v2PitchYaw;
		ns_system::Camera* m_pPerspectiveCamera = nullptr;

	public:


		PlayerController(ns_system::GameObject& a_GameObject)
			: ns_system::Behaviour(a_GameObject)
		{
			ns_system::Input::setCursorEnability(false, false);
			m_pPerspectiveCamera = m_GameObject.getComponent<ns_system::Camera>(ns_system::COMPONENT_TYPE::CAMERA);
		}

	protected:

		virtual void update(float a_fDeltaTime) override
		{
			float l_fVelocity = a_fDeltaTime * 3.0f;

			if (ns_system::Input::IsKeyDown(GLFW_KEY_A))
			{
				m_GameObject.m_Transform.setLocalPosition(m_GameObject.m_Transform.getLocalPosition() + (m_GameObject.m_Transform.getRight() * l_fVelocity));
			}
			else if (ns_system::Input::IsKeyDown(GLFW_KEY_D))
			{
				m_GameObject.m_Transform.setLocalPosition(m_GameObject.m_Transform.getLocalPosition() + (m_GameObject.m_Transform.getRight() * -l_fVelocity));
			}
			
			if (ns_system::Input::IsKeyDown(GLFW_KEY_W))
			{
				m_GameObject.m_Transform.setLocalPosition(m_GameObject.m_Transform.getLocalPosition() + (m_GameObject.m_Transform.getForward() * l_fVelocity));
			}
			else if (ns_system::Input::IsKeyDown(GLFW_KEY_S))
			{
				m_GameObject.m_Transform.setLocalPosition(m_GameObject.m_Transform.getLocalPosition() + (m_GameObject.m_Transform.getForward() * -l_fVelocity));
			}

			ns_system::Input::GetMousePosition(m_MouseX, m_MouseY);
			if (m_bIsFirstRun && m_MouseX == 0.0f && m_MouseY == 0.0f)
			{
				return;
			}

			if (m_bIsFirstRun)
			{
				m_bIsFirstRun = false;
				m_v2LastMouseXY.x = m_MouseX;
				m_v2LastMouseXY.y = m_MouseY;

				glm::vec3 l_v3InitRotation = glm::eulerAngles(m_GameObject.m_Transform.getLocalRotation());

				m_v2PitchYaw.x += (l_v3InitRotation.x / M_PI) * 180.0f;
				m_v2PitchYaw.y += (l_v3InitRotation.y / M_PI) * 180.0f;
			}

			float l_DeltaX = (m_MouseX - m_v2LastMouseXY.x);
			float l_DeltaY = (m_MouseY - m_v2LastMouseXY.y);

			l_DeltaX *= m_fMouseSensitivity;
			l_DeltaY *= m_fMouseSensitivity;

			m_v2LastMouseXY.x = m_MouseX;
			m_v2LastMouseXY.y = m_MouseY;

			m_v2PitchYaw.y += l_DeltaX;
			m_v2PitchYaw.x += l_DeltaY;

			m_GameObject.m_Transform.setLocalRotation(glm::quat({glm::radians(m_v2PitchYaw.x), glm::radians(m_v2PitchYaw.y), 0.0f}));

			int l_iScrollValue = ns_system::Input::GetMouseScroll();
			if (l_iScrollValue == 1 || l_iScrollValue == -1)
			{
				m_pPerspectiveCamera->zoom(5.0f * l_iScrollValue);
			}

			Behaviour::update(a_fDeltaTime);
		}
	};
}