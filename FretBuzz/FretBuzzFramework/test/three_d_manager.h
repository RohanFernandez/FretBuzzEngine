#pragma once

#pragma once

#include "../framework/utils/math.h"
#include "../framework/graphics/shader.h"
#include "../framework/graphics/texture.h"
#include "../framework/components/gameobject_components/camera.h"
#include "../framework/system/core/input.h"

namespace ns_fretBuzz
{
	class three_d_manager : public ns_system::GameObject
	{
	private:
		double m_MouseX, m_MouseY;
		float m_LastMouseX, m_LastMouseY;
		bool m_bIsFirstRun = true;
		float m_fMouseSensitivity = 0.5f;

		float m_fPitch = 0.0f;
		float m_fYaw = 0.0f;

	public:

		ns_system::Camera* m_pPerspectiveCamera = nullptr;

		three_d_manager(GameObject& a_ParentGameObject, std::string a_strName)
			: GameObject(a_ParentGameObject, a_strName, { 0.0f, 0.0f, 5.0f }, { 0.0f, M_PI, 0.0f }, {1.0f, 1.0f, 1.0f})
		{
			ns_system::PerspectiveViewport l_PerspectiveViewport(60.0f, 0.01, 1000.0f );
			m_pPerspectiveCamera = ns_system::Camera::addToGameObject(*this, ns_system::Viewport::PROJECTION_TYPE::PERSPECTIVE, static_cast<ns_system::Viewport*>(&l_PerspectiveViewport));

			ns_system::Input::setCursorEnability(false, false);
		}

		float l_fTime = 0.0f;

		virtual void update(float a_fDeltaTime) override
		{
			float l_fVelocity = a_fDeltaTime * 3.0f;

			if (ns_system::Input::IsKeyDown(GLFW_KEY_A))
			{
				m_Transform.setLocalPosition(m_Transform.getLocalPosition() + (m_Transform.getRight() * l_fVelocity));
			}
			else if (ns_system::Input::IsKeyDown(GLFW_KEY_D))
			{
				m_Transform.setLocalPosition(m_Transform.getLocalPosition() + (m_Transform.getRight() * -l_fVelocity));
			}
			
			if (ns_system::Input::IsKeyDown(GLFW_KEY_W))
			{
				m_Transform.setLocalPosition(m_Transform.getLocalPosition() + (m_Transform.getForward() * l_fVelocity));
			}
			else if (ns_system::Input::IsKeyDown(GLFW_KEY_S))
			{
				m_Transform.setLocalPosition(m_Transform.getLocalPosition() + (m_Transform.getForward() * -l_fVelocity));
			}

			ns_system::Input::GetMousePosition(m_MouseX, m_MouseY);
			if (m_bIsFirstRun && m_MouseX == 0.0f && m_MouseY == 0.0f)
			{
				return;
			}

			if (m_bIsFirstRun)
			{
				m_bIsFirstRun = false;
				m_LastMouseX = m_MouseX;
				m_LastMouseY = m_MouseY;

				glm::vec3 l_v3InitRotation = glm::eulerAngles(m_Transform.getLocalRotation());

				m_fPitch += (l_v3InitRotation.x / M_PI) * 180.0f;
				m_fYaw += (l_v3InitRotation.y / M_PI) * 180.0f;
			}

			float l_DeltaX = (m_MouseX - m_LastMouseX);
			float l_DeltaY = (m_MouseY - m_LastMouseY);

			l_DeltaX *= m_fMouseSensitivity;
			l_DeltaY *= m_fMouseSensitivity;

			m_LastMouseX = m_MouseX;
			m_LastMouseY = m_MouseY;

			m_fYaw += l_DeltaX;
			m_fPitch += l_DeltaY;

			m_Transform.setLocalRotation(glm::quat({glm::radians(m_fPitch), glm::radians(m_fYaw), 0.0f}));

			int l_iScrollValue = ns_system::Input::GetMouseScroll();
			if (l_iScrollValue == 1 || l_iScrollValue == -1)
			{
				m_pPerspectiveCamera->zoom(5.0f * l_iScrollValue);
			}

			GameObject::update(a_fDeltaTime);
		}

		//virtual void render(const ns_system::Camera& a_Camera) override;*/
	};
}