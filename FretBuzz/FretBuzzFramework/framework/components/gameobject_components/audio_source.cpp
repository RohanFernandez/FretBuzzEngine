#pragma once
#include "audio_source.h"
#include "system/core/resource_manager.h"
#include "system/game_object.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{	
		AudioSource::AudioSource(GameObject& a_GameObj)
			: IComponent(COMPONENT_TYPE::AUDIO_SOURCE, a_GameObj)
		{
			m_pISoundEngine = AudioEngine::s_pInstance->m_pISoundEngine;
		}

		AudioSource::AudioSource(GameObject& a_GameObj, AudioClip* a_AudioClip)
			:AudioSource(a_GameObj)
		{
			setAudioClip(a_AudioClip);
		}

		AudioSource::AudioSource(GameObject& a_GameObj, std::string a_strAudioClipResourceName)
			: AudioSource(a_GameObj)
		{
			setAudioClip(a_strAudioClipResourceName);
		}

		AudioSource* AudioSource::addToGameObject(GameObject& a_GameObj)
		{
			return IComponent::isComponentOfTypeExistInGameObj(COMPONENT_TYPE::AUDIO_SOURCE, &a_GameObj) ?
				nullptr : new AudioSource(a_GameObj);
		}

		AudioSource* AudioSource::addToGameObject(GameObject& a_GameObj, AudioClip* a_AudioClip)
		{
			return IComponent::isComponentOfTypeExistInGameObj(COMPONENT_TYPE::AUDIO_SOURCE, &a_GameObj) ?
				nullptr : new AudioSource(a_GameObj, a_AudioClip);
		}

		AudioSource* AudioSource::addToGameObject(GameObject& a_GameObj, std::string a_strAudFilePath)
		{
			return IComponent::isComponentOfTypeExistInGameObj(COMPONENT_TYPE::AUDIO_SOURCE, &a_GameObj) ?
				nullptr : new AudioSource(a_GameObj, a_strAudFilePath);
		}

		void AudioSource::setAudioClip(AudioClip* a_AudioClip)
		{
			stop();
			m_pISoundSource = a_AudioClip->getSoundSource();
			m_fVolume = m_pISoundSource->getDefaultVolume();
		}

		void AudioSource::setAudioClip(std::string a_strAudioClipResourceName)
		{
			stop();
			m_pISoundSource = ResourceManager::getResource<AudioClip>(a_strAudioClipResourceName.c_str())->m_pISoundSource;
			m_fVolume = m_pISoundSource->getDefaultVolume();
		}

		AudioSource::~AudioSource()
		{
			stop();
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