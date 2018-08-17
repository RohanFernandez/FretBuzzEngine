#pragma once
#include <irrKlang.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class AudioEngine
		{
		friend class AudioSource;
		friend class AudioClip;
		private:
			//singleton
			static AudioEngine* s_pInstance;

			irrklang::ISoundEngine* m_pISoundEngine = nullptr;

		public:
			AudioEngine();
			~AudioEngine();
		};
	}
}