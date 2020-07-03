#pragma once

#include "system/component.h"
#include "../audio_clip.h"

namespace ns_fretBuzz
{
	class GameObject;
	class  AudioSource : public IComponent
	{
	private:
		irrklang::ISoundEngine* m_pISoundEngine = nullptr;
		irrklang::ISoundSource* m_pISoundSource = nullptr;
		irrklang::ISound* m_pISound = nullptr;

		float m_fVolume = 0.0f;
		bool m_bIsLooping = false;
		bool m_bIsPlayOnAwake = true;


	protected:
		virtual ~AudioSource();

		virtual void editorInspectorRender() override;

		virtual void onEnable() override;
		virtual void onDisable() override;

	public:
		AudioSource(GameObject* a_GameObj, bool a_bIsPlayOnAwake = false);
		AudioSource(GameObject* a_GameObj, AudioClip* a_AudioClip, bool a_bIsPlayOnAwake = false);
		AudioSource(GameObject* a_GameObj, std::string a_strAudFilePath, bool a_bIsPlayOnAwake = false);

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

		void setPlayOnAwake(bool a_bIsPlayOnAwake);
		bool isPlayOnAwake() const;
	};
}