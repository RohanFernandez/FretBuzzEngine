#pragma once
#include "audio_source.h"
#include "../../system/resource_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{	
		AudioSource::AudioSource()
			: IComponent(COMPONENT_TYPE::AUDIO_SOURCE)
		{
			m_pISoundEngine = AudioEngine::s_pInstance->m_pISoundEngine;
		}

		AudioSource::AudioSource(AudioClip* a_AudioClip)
			:AudioSource()
		{
			setAudioClip(a_AudioClip);
		}

		AudioSource::AudioSource(AudioSource& a_AudSrc)
			: AudioSource()
		{
			setAudioClip(a_AudSrc);
		}

		AudioSource::AudioSource(AudioSource&& a_AudSrc)
			: AudioSource()
		{
			setAudioClip(a_AudSrc);
		}

		AudioSource::AudioSource(std::string a_strAudioClipResourceName)
			: AudioSource()
		{
			setAudioClip(a_strAudioClipResourceName);
		}

		void AudioSource::setAudioClip(AudioClip* a_AudioClip)
		{
			stop();
			m_pISoundSource = a_AudioClip->getSoundSource();
			m_fVolume = m_pISoundSource->getDefaultVolume();
		}

		void AudioSource::setAudioClip(AudioSource& a_AudSrc)
		{
			stop();
			m_pISoundSource = a_AudSrc.m_pISoundSource;
			m_bIsLooping = a_AudSrc.m_bIsLooping;
			m_fVolume = a_AudSrc.m_fVolume;
		}

		void AudioSource::setAudioClip(std::string a_strAudioClipResourceName)
		{
			stop();
			m_pISoundSource = ResourceManager::getResource<AudioClip>(a_strAudioClipResourceName.c_str())->m_pISoundSource;
			m_fVolume = m_pISoundSource->getDefaultVolume();
		}

		AudioSource::~AudioSource()
		{
			m_pISoundEngine = nullptr;
			m_pISoundSource = nullptr;
			m_pISound = nullptr;
		}

		void AudioSource::play()
		{
			if (m_pISound != nullptr)
			{
				m_pISound->setIsPaused(false);
			}
			else
			{
				restart();
			}
		}

		void AudioSource::restart()
		{
			if (m_pISoundSource == nullptr)
			{
				std::cout << "AudioSource::restart:: No audio clip is set in the audio source.\n";
				return;
			}
			stop();
			m_pISound = m_pISoundEngine->play2D(m_pISoundSource, m_bIsLooping, true);
			m_pISound->setVolume(m_fVolume);
			m_pISound->setIsPaused(false);
		}

		void AudioSource::pause()
		{
			if (m_pISound != nullptr)
			{
				m_pISound->setIsPaused();
			}
		}

		void AudioSource::stop()
		{
			if (m_pISound != nullptr)
			{
				m_pISound->stop();
				m_pISound->drop();
				m_pISound = nullptr;
			}
		}

		void AudioSource::setVolume(float a_fVolume)
		{
			m_fVolume = a_fVolume;
			if (m_pISound != nullptr)
			{
				m_pISound->setVolume(m_fVolume);
			}
		}

		float AudioSource::getVolume() const
		{
			return m_fVolume;
		}

		float AudioSource::getLength() const
		{
			return m_pISoundSource->getPlayLength();
		}

		bool AudioSource::getIsLooping() const
		{
			return m_bIsLooping;
		}

		void AudioSource::setLooping(bool a_bIsLoop)
		{
			m_bIsLooping = a_bIsLoop;
			if (m_pISound != nullptr)
			{
				m_pISound->setIsLooped(m_bIsLooping);
			}
		}

		bool AudioSource::getIsFinishedPlaying() const
		{
			return m_pISound == nullptr ? true : m_pISound->isFinished();
		}
	}
}