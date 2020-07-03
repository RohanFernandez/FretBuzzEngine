#pragma once
#include <irrKlang.h>

namespace ns_fretBuzz
{
	class  AudioEngine
	{
	friend class AudioSource;
	friend class AudioClip;
	private:
		//singleton
		static AudioEngine* s_pInstance;

		irrklang::ISoundEngine* m_pISoundEngine = nullptr;

		AudioEngine();
		~AudioEngine();

	public:
		static AudioEngine* initialize();
		void destroy();

		static const AudioEngine* get();

		static void ToggleMute(bool a_bIsPaused);
	};
}