#pragma once
#include "audio_engine.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//singleton Instance
		AudioEngine* AudioEngine::s_pInstance = nullptr;

		AudioEngine::AudioEngine()
		{
			if (s_pInstance != nullptr)
			{
				return;
			}
			s_pInstance = this;
			m_pISoundEngine = irrklang::createIrrKlangDevice();
		}

		AudioEngine::~AudioEngine()
		{
			if (s_pInstance != this)
			{
				return;
			}

			m_pISoundEngine->drop();
			m_pISoundEngine = nullptr;
			s_pInstance = nullptr;
		}
	
	}
}