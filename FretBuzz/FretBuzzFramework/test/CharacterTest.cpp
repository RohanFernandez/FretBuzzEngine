#pragma once

#include "CharacterTest.h"
#include "../framework/system/core/resource_manager.h"
#include "../framework/components/gameobject_components/sprite_renderer.h"

#include <ft2build.h>
#include "../framework/system/core/system.h"
//#include FT_FREETYPE_H

namespace ns_fretBuzz
{

	CharacterTest::CharacterTest(GameObject& a_ParentGameObject , std::string a_Name, ns_system::GameObject* a_TestGameObject)
		: ns_system::GameObject(a_ParentGameObject, a_Name, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f })
		{
			m_pAudSrc = ns_system::AudioSource::addToGameObject(*this, "beats");
			m_pSpriteAnimator = ns_system::SpriteAnimationController::addToGameObject(*this, "Character" );
			m_pRectCollider = ns_system::RectCollider::addToGameObject(*this, {50.0f, 50.0f }, false, true);

			m_pAudSrc->play();
			m_pAudSrc->setLooping(true);

			m_pTestGameObject = a_TestGameObject;
		}

		void CharacterTest::update(float a_fDeltaTime)
		{
			if (ns_system::Input::IsKeyDown(GLFW_KEY_G))
			{
				m_pAudSrc->play();
			}

			if (ns_system::Input::IsKeyDown(GLFW_KEY_H))
			{
				m_pAudSrc->restart();
			}

			if (ns_system::Input::IsKeyDown(GLFW_KEY_J))
			{
				m_pAudSrc->stop();
			}

			if (ns_system::Input::IsKeyDown(GLFW_KEY_K))
			{
				m_pAudSrc->pause();
			}

			if (ns_system::Input::IsKeyPutDown(GLFW_KEY_U))
			{
				m_pSpriteAnimator->play("idle");
			}

			if (ns_system::Input::IsMouseBtnPutUp(GLFW_MOUSE_BUTTON_1))
			{
				m_pSpriteAnimator->play("slash");
			}

			float l_fCurrentSpeed = m_fVelocity;

			float l_fHorizontalVelocity = 0.0f;
			float l_fVerticalVelocity = 0.0f;


			if (ns_system::Input::IsKeyDown(GLFW_KEY_W))
			{
				l_fVerticalVelocity += l_fCurrentSpeed;
			}


			if (ns_system::Input::IsKeyDown(GLFW_KEY_S))
			{
				l_fVerticalVelocity -= l_fCurrentSpeed;
			}
			if (ns_system::Input::IsKeyDown(GLFW_KEY_A))
			{
				l_fHorizontalVelocity -= l_fCurrentSpeed;
			}
			if (ns_system::Input::IsKeyDown(GLFW_KEY_D))
			{
				l_fHorizontalVelocity += l_fCurrentSpeed;
			}

			m_pRectCollider->setLinearVelocity({ l_fHorizontalVelocity, l_fVerticalVelocity });

			if (ns_system::Input::IsKeyDown(GLFW_KEY_R))
			{
				m_fScale += a_fDeltaTime * m_fScaleVelocity;
				m_Transform.scale({ m_fScale, m_fScale,0.0f });
			}
			else if (ns_system::Input::IsKeyDown(GLFW_KEY_E))
			{
				m_fScale -= a_fDeltaTime * m_fScaleVelocity;
				m_Transform.scale({ m_fScale, m_fScale,0.0f });
			}

			if (ns_system::Input::IsKeyPutDown(GLFW_KEY_0))
			{
				m_pTestGameObject->setActive(!m_pTestGameObject->getIsActiveInHierarchy());
			}

			ns_system::Input::GetMousePosition(m_dMouseX, m_dMouseY);

			glm::vec3 l_MousePosition = glm::vec3((float)m_dMouseX - ns_system::Window::getWidth() / 2.0f, ns_system::Window::getHeight() / 2.0f - (float)m_dMouseY, 0.0f);
			glm::vec3 l_v3PlayerPosition = m_Transform.getPosition();
			
			glm::vec3 l_v3PlayerToMouseDirection = glm::normalize(l_MousePosition - l_v3PlayerPosition);
			float l_fAngleToRotate = (glm::acos(glm::dot(l_v3PlayerToMouseDirection, { 1.0f,0.0f,0.0f })));
			if (!glm::isnan(l_fAngleToRotate))
			{
				if (l_MousePosition.y < l_v3PlayerPosition.y) { l_fAngleToRotate = -l_fAngleToRotate; }
				m_Transform.rotate({ 0.0f, 0.0f, l_fAngleToRotate });
			}

			//std::cout << "Angle to rotate :: "<< l_fAngleToRotate <<"\n";
			ns_system::GameObject::update(a_fDeltaTime);
		};

		void CharacterTest::render(const glm::mat4& a_mat4Transformation, const ns_system::Viewport& a_Camera)
		{
			GameObject::render(a_mat4Transformation,a_Camera);
		};
	}