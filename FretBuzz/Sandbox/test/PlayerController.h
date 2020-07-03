#pragma once

#include "framework/components/gameobject_components/camera.h"
#include <input.h>

#include "framework/components/gameobject_components/behaviour.h"

#include <imgui/imgui.h>

namespace ns_HMGame
{
	class PlayerController : public ns_fretBuzz::Behaviour
	{
	private:
		double m_MouseX, m_MouseY;
		bool m_bIsFirstRun = true;
		float m_fMouseSensitivity = 0.3f;

		glm::vec2 m_v2LastMouseXY;
		glm::vec3 m_v3PitchYawRoll;
		ns_fretBuzz::Camera* m_pPerspectiveCamera = nullptr;

	public:

		PlayerController(ns_fretBuzz::GameObject* a_GameObject)
			: ns_fretBuzz::Behaviour(a_GameObject)
		{
			ns_fretBuzz::Input::setCursorEnability(true, true);
			m_pPerspectiveCamera = m_GameObject.getComponent<ns_fretBuzz::Camera>(ns_fretBuzz::COMPONENT_TYPE::CAMERA);
		}

	protected:

		virtual void update(const float& a_fDeltaTime) override
		{
			float l_fVelocity = a_fDeltaTime * 3.0f;

			if (ns_fretBuzz::Input::IsKeyDown(GLFW_KEY_A))
			{
				m_GameObject.m_Transform.setLocalPosition(m_GameObject.m_Transform.getLocalPosition() + (m_GameObject.m_Transform.getRight() * l_fVelocity));
			}
			else if (ns_fretBuzz::Input::IsKeyDown(GLFW_KEY_D))
			{
				m_GameObject.m_Transform.setLocalPosition(m_GameObject.m_Transform.getLocalPosition() + (m_GameObject.m_Transform.getRight() * -l_fVelocity));
			}
			
			if (ns_fretBuzz::Input::IsKeyDown(GLFW_KEY_W))
			{
				m_GameObject.m_Transform.setLocalPosition(m_GameObject.m_Transform.getLocalPosition() + (m_GameObject.m_Transform.getForward() * l_fVelocity));
			}
			else if (ns_fretBuzz::Input::IsKeyDown(GLFW_KEY_S))
			{
				m_GameObject.m_Transform.setLocalPosition(m_GameObject.m_Transform.getLocalPosition() + (m_GameObject.m_Transform.getForward() * -l_fVelocity));
			}

			ns_fretBuzz::Input::GetMousePosition(m_MouseX, m_MouseY);
			if (m_bIsFirstRun && m_MouseX == 0.0f && m_MouseY == 0.0f)
			{
				return;
			}

			if (m_bIsFirstRun)
			{
				m_bIsFirstRun = false;
				m_v2LastMouseXY.x = (float)m_MouseX;
				m_v2LastMouseXY.y = (float)m_MouseY;

				glm::vec3 l_v3InitRotation = glm::eulerAngles(m_GameObject.m_Transform.getLocalRotation());

				m_v3PitchYawRoll.x = (l_v3InitRotation.x);
				m_v3PitchYawRoll.y = (l_v3InitRotation.y);
				m_v3PitchYawRoll.z = (l_v3InitRotation.z);
			}

			float l_DeltaX = (float)(m_MouseX - m_v2LastMouseXY.x);
			float l_DeltaY = (float)(m_v2LastMouseXY.y - m_MouseY);

			l_DeltaX *= m_fMouseSensitivity;
			l_DeltaY *= m_fMouseSensitivity;

			m_v2LastMouseXY.x = (float)m_MouseX;
			m_v2LastMouseXY.y = (float)m_MouseY;

			m_v3PitchYawRoll.y += glm::radians(l_DeltaX);
			m_v3PitchYawRoll.x -= glm::radians(l_DeltaY);

			m_GameObject.m_Transform.setLocalRotation(glm::quat({m_v3PitchYawRoll.x, m_v3PitchYawRoll.y, m_v3PitchYawRoll.z}));

			int l_iScrollValue = ns_fretBuzz::Input::GetMouseScroll();
			if (l_iScrollValue == 1 || l_iScrollValue == -1)
			{
				m_pPerspectiveCamera->zoom(5.0f * l_iScrollValue);
			}


			/*if (Input::IsKeyPutDown(GLFW_KEY_I))
			{
				SceneManager::s_loadScene("initstate");
			}*/

			/*if (Input::IsKeyPutDown(GLFW_KEY_O))
			{
				SceneManager::s_loadScene("3d_Test");
			}*/

			Behaviour::update(a_fDeltaTime);
		}

		virtual void render(const glm::mat4& a_mat4Transformation, const ns_fretBuzz::Camera& a_Camera) override
		{
			Behaviour::render(a_mat4Transformation,a_Camera);
		}
	};
}