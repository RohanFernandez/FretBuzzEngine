#pragma once

#include "CharacterTest.h"
#include "../framework/system/core/resource_manager.h"
#include "../framework/components/gameobject_components/sprite_renderer.h"
#include "../framework/components/gameobject_components/image.h"

#include "../framework/system/core/system.h"
#include <iostream>
//#include FT_FREETYPE_H

namespace ns_fretBuzz
{

	CharacterTest::CharacterTest(ns_system::GameObject& a_ParentGameObject , std::string a_Name, ns_system::GameObject* a_CamGameObject, GameObject& a_refOriginGameObject)
		: ns_system::GameObject2D(a_ParentGameObject, a_Name, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 1.0f }, { 150.0f, 100.0f }, true)
		{
			m_pAudSrc = ns_system::AudioSource::addToGameObject(*this, "beats");
			m_pSpriteAnimator = ns_system::SpriteAnimationController::addToGameObject(*this, "Character" );
			m_pRectCollider = ns_system::RectCollider::addToGameObject(*this, { 50.0f, 50.0f }, ns_system::PhysicsEngine::PHYSICS_BODY_TYPE::DYNAMIC, true);

			m_pAudSrc->play();
			m_pAudSrc->setLooping(true);

			m_pcamGameObj = a_CamGameObject;

			m_pRefOriginGameObject = &a_refOriginGameObject;
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

			if (ns_system::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_1))
			{
				if (m_iCurrentWeaponID == 0)
				{
					m_pSpriteAnimator->play("slash");
				}
				else
				{
					m_pSpriteAnimator->play("mp5ShootTrigger");

					double l_dMouseX, l_dMouseY;
					ns_system::Input::GetMousePosition(l_dMouseX, l_dMouseY);
					glm::vec2 l_MousePosition = glm::vec2((float)m_dMouseX - (ns_graphics::Window::getWidth() * 0.5f), (ns_graphics::Window::getHeight() * 0.5f) - (float)m_dMouseY);

					glm::vec2 l_WorldPosition = m_Transform.getWorldPosition();
					glm::vec3 l_v3GLMDirection = glm::normalize(glm::vec3(l_MousePosition.x, l_MousePosition.y, 0.0f));

					b2Vec2 l_v2Direction = b2Vec2{ l_v3GLMDirection.x, l_v3GLMDirection.y };
					b2Vec2 l_v2DirectionImpulse = l_v2Direction;

					l_v2Direction *= 140.0f;

					GameObject2D* l_pBulletGameObject = ns_system::GameObject2D::instantiate(*m_pRefOriginGameObject, "bullet", glm::vec3(l_WorldPosition.x, l_WorldPosition.y, 0.0f) + glm::vec3(l_v2Direction.x, l_v2Direction.y, 0.0f), glm::eulerAngles(m_Transform.getLocalRotation()), { 1.0f, 1.0f, 1.0f }, glm::vec2(12.0f, 4.0f));
					ns_graphics::Image::addToGameObject(*l_pBulletGameObject, ns_system::ResourceManager::getResource<ns_graphics::SpriteGroup>("bullet")->getSprite(0), {1.0f, 1.0f, 0.0f, 1.0f});
					ns_system::RectCollider* l_pRectCollider = ns_system::RectCollider::addToGameObject(*l_pBulletGameObject, ns_system::PhysicsEngine::PHYSICS_BODY_TYPE::DYNAMIC, false,true);

					l_v2DirectionImpulse *= 3000.0f;
					l_pRectCollider->setLinearVelocity(l_v2DirectionImpulse);
				}
			}

			if (ns_system::Input::IsMouseBtnPutDown(GLFW_MOUSE_BUTTON_2))
			{
				m_iCurrentWeaponID = m_iCurrentWeaponID == 0 ? 1 : 0;

				if (m_iCurrentWeaponID == 0)
				{
					m_pSpriteAnimator->play("idle");
				}
				else
				{
					m_pSpriteAnimator->play("mp5WalkTrigger");
				}
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

			if (l_fHorizontalVelocity != 0.0f &&
				l_fVerticalVelocity != 0.0f)
			{
				l_fHorizontalVelocity *= 0.7f;
				l_fVerticalVelocity *= 0.7f;
			}

			m_pRectCollider->setLinearVelocity({ l_fHorizontalVelocity, l_fVerticalVelocity });
			m_pcamGameObj->m_Transform.setWorldPosition(m_pTransform->getWorldPosition());

			if (ns_system::Input::IsKeyDown(GLFW_KEY_R))
			{
				m_fScale += a_fDeltaTime * m_fScaleVelocity;
				m_pTransform->setLocalScale({ m_fScale, m_fScale,0.0f });
			}
			else if (ns_system::Input::IsKeyDown(GLFW_KEY_E))
			{
				m_fScale -= a_fDeltaTime * m_fScaleVelocity;
				m_pTransform->setLocalScale({ m_fScale, m_fScale,0.0f });
			}

			ns_system::Input::GetMousePosition(m_dMouseX, m_dMouseY);

			glm::vec3 l_MousePosition = glm::vec3((float)m_dMouseX - (ns_graphics::Window::getWidth() * 0.5f), (ns_graphics::Window::getHeight() * 0.5f) - (float)m_dMouseY, 0.0f);
			glm::vec3 l_v3PlayerPosition = m_pTransform->getLocalPosition();
			
			glm::vec3 l_v3PlayerToMouseDirection = glm::normalize(l_MousePosition);

			float a_fZ = glm::atan(l_v3PlayerToMouseDirection.x, l_v3PlayerToMouseDirection.y);
			m_pTransform->setLocalRotation({ 0.0f, 0.0f, -a_fZ + M_PI_2 });

			//std::cout << "Angle to rotate :: "<< l_fAngleToRotate <<"\n";
			ns_system::GameObject::update(a_fDeltaTime);
		};

		void CharacterTest::render(const ns_graphics::Camera& a_Camera)
		{
			GameObject::render(a_Camera);
		};
	}