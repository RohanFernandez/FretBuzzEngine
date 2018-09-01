#pragma once
#include "../framework/system/scene_manager.h"
#include "../framework/graphics/shader.h"
#include "../framework/graphics/texture.h"

#include "../test/CharacterTest.h"

namespace ns_fretBuzz
{
	class InitState : 
		public ns_system::IScene
	{
	public:
		ns_system::GameObject* m_goParentGameObj;

		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_IBO;
		bool isAudioPlaying = false;

		InitState(std::string a_strSceneName);
			
		virtual void OnStateEnter() override;

		virtual void OnStateExit() override;
	};
}