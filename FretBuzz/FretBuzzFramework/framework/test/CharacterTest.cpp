#pragma once

#include "CharacterTest.h"
#include "../system/resource_manager.h"
#include "../components/sprite/sprite_renderer.h"

namespace ns_fretBuzz
{

		CharacterTest::CharacterTest() 
			: ns_system::GameObject("character_test")
		{
			m_pAudSrc = ns_system::AudioSource::addToGameObject(*this, "beats");
			ns_graphics::SpriteRenderer::addToGameObject(*this);
			m_pSpriteAnimator =  ns_system::SpriteAnimator::addToGameObject(*this, std::vector<std::string>{"dark", "sword_walk","sword_slash"});
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

			if (ns_system::Input::IsKeyDown(GLFW_KEY_U))
			{
				m_pSpriteAnimator->play("sword_walk");
			}

			if (ns_system::Input::IsKeyDown(GLFW_KEY_Y))
			{
				m_pSpriteAnimator->play("sword_slash");
			}

			ns_system::GameObject::update(a_fDeltaTime);
		};

		void CharacterTest::render(const ns_system::Camera& a_Camera)
		{
			GameObject::render(a_Camera);
		};
	}