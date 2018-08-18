#pragma once

#include "../game/game_object.h" 
#include "../components/audio/audio_source.h"


#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../components/camera/camera.h"
#include "../system/input.h"

namespace ns_fretBuzz
{
	class CharacterTest : public ns_system::GameObject
	{
	private:
		ns_system::AudioSource* m_pAudSrc = nullptr;

		ns_graphics::Shader* m_pShader = nullptr;
		ns_graphics::Texture* m_pTexture = nullptr;

		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_IBO;
		bool isAudioPlaying = false;

		GLfloat m_vertices[20] =
		{
			-0.5,-0.5, 0.0, 0.0, 0.0,
			-0.5, 0.5, 0.0, 0.0, 1.0,
			0.5,  0.5, 0.0, 1.0, 1.0,
			0.5, -0.5, 0.0, 1.0, 0.0
		};

		GLuint m_indices[6] =
		{
			0, 1, 2,
			2, 3, 0
		};


	public:

		CharacterTest();

		virtual void update(float a_fDeltaTime) override;
		virtual void render() override;
	};
}