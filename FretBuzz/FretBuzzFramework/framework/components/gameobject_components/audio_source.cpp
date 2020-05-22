#include <fretbuzz_pch.h>
#include "audio_source.h"
#include "system/core/resource_manager.h"
#include "system/game_object.h"
#include <imgui/imgui.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{	
		AudioSource::AudioSource(GameObject* a_GameObj, bool a_bIsPlayOnAwake)
			: IComponent(COMPONENT_TYPE::AUDIO_SOURCE, a_GameObj)
		{
			m_pISoundEngine = AudioEngine::s_pInstance->m_pISoundEngine;
			setPlayOnAwake(a_bIsPlayOnAwake);
		}

		AudioSource::AudioSource(GameObject* a_GameObj, AudioClip* a_AudioClip, bool a_bIsPlayOnAwake)
			:AudioSource(a_GameObj, a_bIsPlayOnAwake)
		{
			setAudioClip(a_AudioClip);
		}

		AudioSource::AudioSource(GameObject* a_GameObj, std::string a_strAudioClipResourceName, bool a_bIsPlayOnAwake)
			: AudioSource(a_GameObj, a_bIsPlayOnAwake)
		{
			setAudioClip(a_strAudioClipResourceName);
		}

		void AudioSource::onEnable()
		{
			if(isPlayOnAwake())
			{ 
				play();
			}
		}

		void AudioSource::onDisable()
		{
			stop();
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
			return (float)m_pISoundSource->getPlayLength();
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

		void AudioSource::setPlayOnAwake(bool a_bIsPlayOnAwake)
		{
			m_bIsPlayOnAwake = a_bIsPlayOnAwake;
		}

		bool AudioSource::isPlayOnAwake() const
		{
			return m_bIsPlayOnAwake;
		}

		void AudioSource::editorInspectorRender()
		{
			IComponent::editorInspectorRender();

			//Is play on awake
			bool l_bIsPlayOnAwake = isPlayOnAwake();
			ImGui::Text("Play on awake");
			ImGui::SameLine(150);
			bool l_bIsToggledPlayOnAwake = ImGui::Checkbox("##IsPlayOnAwake", &l_bIsPlayOnAwake);
			if (l_bIsToggledPlayOnAwake)
			{
				setPlayOnAwake(l_bIsPlayOnAwake);
			}

			//Is looping
			bool l_bIsLooping = getIsLooping();
			ImGui::Text("Is Looped");
			ImGui::SameLine(150);
			bool l_IsLoopChecked = ImGui::Checkbox("##IsLoop", &l_bIsLooping);
			if (l_IsLoopChecked)
			{
				setLooping(l_bIsLooping);
			}

			//Volume
			float l_fCurentVolume = getVolume();;
			ImGui::Text("Volume");
			ImGui::SameLine(150);
			ImGui::SliderFloat("##Volume", &l_fCurentVolume, 0.0f, 1.0f);
			setVolume(l_fCurentVolume);

			//Audio clip name
			ImGui::Text("Clip");
			ImGui::SameLine(150);
			ImGui::Text(m_pISoundSource == nullptr ? "" : m_pISoundSource->getName());
		}
	}
}