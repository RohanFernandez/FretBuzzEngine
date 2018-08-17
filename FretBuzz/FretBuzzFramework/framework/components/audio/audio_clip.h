#pragma once
#include "../../system/managers/managed_resource.h"
#include "../../system/managers/audio_engine.h"
#include <string>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class AudioClip : public IManagedResource
		{
		private:
			friend class AudioSource;

			irrklang::ISoundEngine* m_pISoundEngine = nullptr;
			irrklang::ISoundSource* m_pISoundSource = nullptr;

			inline irrklang::ISoundSource* getSoundSource()
			{
				return m_pISoundSource;
			}

		public:
			AudioClip(std::string a_strAudioFilePath);
			AudioClip(AudioClip& a_AudClip);
			AudioClip() = delete;
			virtual ~AudioClip();

			virtual void destroyResource() override;
		};
	}
}