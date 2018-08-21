#pragma once

#include "CharacterTest.h"
#include "../system/resource_manager.h"

namespace ns_fretBuzz
{

		CharacterTest::CharacterTest() 
			: ns_system::GameObject("character_test")
		{
			m_pAudSrc = ns_system::AudioSource::addToGameObject(*this, "beats");
			
			m_pShader = ns_system::ResourceManager::getResource<ns_graphics::Shader>("simple");
			m_pTexture = ns_system::ResourceManager::getResource<ns_graphics::Texture>("darksider");

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

				ns_system::GameObject::update(a_fDeltaTime);
			}
		};

		void CharacterTest::render(const ns_system::Camera& a_Camera)
		{
			GameObject::render(a_Camera);
		};
	}