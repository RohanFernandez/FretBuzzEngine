#pragma once

#include "../../game/component.h"
#include "audio_clip.h"
#include <string>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class GameObject;
		class AudioSource : public IComponent
		{
		private:
			static constexpr COMPONENT_TYPE s_COMPONENT_TYPE = COMPONENT_TYPE::AUDIO_SOURCE;

			irrklang::ISoundEngine* m_pISoundEngine = nullptr;
			irrklang::ISoundSource* m_pISoundSource = nullptr;
			irrklang::ISound* m_pISound = nullptr;

			float m_fVolume = 0.0f;
			bool m_bIsLooping = false;

			AudioSource(GameObject& a_GameObj);
			AudioSource(GameObject& a_GameObj, AudioClip* a_AudioClip);
			AudioSource(GameObject& a_GameObj, std::string a_strAudFilePath);

			~AudioSource();

		public:

			static AudioSource* addToGameObject(GameObject& a_GameObj);
			static AudioSource* addToGameObject(GameObject& a_GameObj, AudioClip* a_AudioClip);
			static AudioSource* addToGameObject(GameObject& a_GameObj, std::string a_strAudFilePath);

			void setAudioClip(AudioClip* a_AudioClip);
			void setAudioClip(std::string a_strAudioClipResourceName);
			
			void play();
			void stop();
			void pause();
			void restart();

			void setVolume(float a_fVolume);
			float getVolume() const;
			float getLength() const;
			bool getIsLooping() const;
			void setLooping(bool a_bIsLoop);
			bool getIsFinishedPlaying() const;
		};
	}
}