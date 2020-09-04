#include <fretbuzz_pch.h>
#include "audio_engine.h"

namespace FRETBUZZ
{
	//singleton Instance
	AudioEngine* AudioEngine::s_pInstance = nullptr;

	AudioEngine* AudioEngine::initialize()
	{
		if (s_pInstance != nullptr)
		{
			std::cout << "AudioEngine::initialize:: Audio Engine already exists.\n";
			return nullptr;
		}

		s_pInstance = new AudioEngine();
		return s_pInstance;
	}

	void AudioEngine::destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	AudioEngine::AudioEngine()
	{
		m_pISoundEngine = irrklang::createIrrKlangDevice();
	}

	AudioEngine::~AudioEngine()
	{
		m_pISoundEngine->drop();
		m_pISoundEngine = nullptr;
		s_pInstance = nullptr;
	}

	const AudioEngine* AudioEngine::get()
	{
		return s_pInstance;
	}

	void AudioEngine::ToggleMute(bool a_bIsPaused)
	{
		s_pInstance->m_pISoundEngine->setAllSoundsPaused(a_bIsPaused);
	}
}