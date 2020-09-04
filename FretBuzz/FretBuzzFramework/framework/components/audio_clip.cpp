#include <fretbuzz_pch.h>
#include "audio_clip.h"
#include <resource_manager.h>

namespace FRETBUZZ
{
	AudioClip::AudioClip(std::string a_strAudioFilePath)
		: IManagedResource()
	{
		m_pISoundEngine = AudioEngine::s_pInstance->m_pISoundEngine;
		m_pISoundSource = m_pISoundEngine->addSoundSourceFromFile(a_strAudioFilePath.c_str());
	}

	AudioClip::AudioClip(AudioClip& a_AudClip)
		: IManagedResource(a_AudClip.m_bIsErrorWhileLoading)
	{
		m_pISoundEngine = a_AudClip.m_pISoundEngine;
		m_pISoundSource = a_AudClip.m_pISoundSource;
	}

	AudioClip::AudioClip(AudioClip&& a_AudClip)
		: IManagedResource(a_AudClip.m_bIsErrorWhileLoading)
	{
		m_pISoundEngine = a_AudClip.m_pISoundEngine;
		m_pISoundSource = a_AudClip.m_pISoundSource;
	}

	AudioClip::~AudioClip()
	{
			
	}

	void AudioClip::destroyResource()
	{
		m_pISoundEngine->removeSoundSource(m_pISoundSource);
	}
}