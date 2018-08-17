#pragma once
#include "audio_clip.h"
#include "../../system/managers/resource_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		AudioClip::AudioClip(std::string a_strAudioFilePath)
			: IManagedResource()
		{
			m_pISoundEngine = AudioEngine::s_pInstance->m_pISoundEngine;
			m_pISoundSource = m_pISoundEngine->addSoundSourceFromFile(a_strAudioFilePath.c_str());
		}

		AudioClip::AudioClip(AudioClip& a_AudClip)
			: IManagedResource()
		{
			m_pISoundEngine = a_AudClip.m_pISoundEngine;
			m_pISoundSource = a_AudClip.m_pISoundSource;

			a_AudClip.m_pISoundEngine = nullptr;
			a_AudClip.m_pISoundSource = nullptr;
		}

		AudioClip::~AudioClip()
		{
			
		}

		void AudioClip::destroyResource()
		{
			std::cout << "Unloading audio clip resource\n";
			m_pISoundEngine->removeSoundSource(m_pISoundSource);
		}
	}
}