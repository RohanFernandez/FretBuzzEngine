#pragma once
#include "system/core/managed_resource.h"
#include "system/core/audio_engine.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class  AudioClip : public IManagedResource
		{
		private:
			friend class AudioSource;
			//friend class ResourceManager::Resource<AudioClip>::ResourceData;

			irrklang::ISoundEngine* m_pISoundEngine = nullptr;
			irrklang::ISoundSource* m_pISoundSource = nullptr;

			inline irrklang::ISoundSource* getSoundSource()
			{
				return m_pISoundSource;
			}

		protected:
			virtual void destroyResource() override;

		public:
			AudioClip(std::string a_strAudioFilePath);
			AudioClip(AudioClip& a_AudClip);
			AudioClip(AudioClip&& a_AudClip);
			AudioClip() = delete;
			virtual ~AudioClip();
		};
	}
}