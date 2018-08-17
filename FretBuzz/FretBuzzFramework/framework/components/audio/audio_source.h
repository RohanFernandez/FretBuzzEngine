#pragma once

#include "audio_clip.h"
#include <string>; 

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class AudioSource
		{
		private:
			irrklang::ISoundEngine* m_pISoundEngine = nullptr;
			irrklang::ISoundSource* m_pISoundSource = nullptr;
			irrklang::ISound* m_pISound = nullptr;

			float m_fVolume = 0.0f;
			bool m_bIsLooping = false;

		public:
			AudioSource();
			AudioSource(AudioClip* a_AudioClip);
			AudioSource(AudioSource& a_AudSrc);
			AudioSource(std::string a_strAudFilePath);

			~AudioSource();

			void setAudioClip(AudioClip* a_AudioClip);
			void setAudioClip(AudioSource& a_AudSrc);
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