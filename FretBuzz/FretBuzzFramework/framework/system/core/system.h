#pragma once

#include "audio_engine.h"
#include "master_renderer.h"
#include "input.h"
#include "resource_manager.h"
#include "physics_engine.h"
#include "../scene_manager.h"
#include "../game_startup.h"
#include <system/editor/editor_inspector.h>
#include "layer/layer_manager.h"
#include "graphics/font_manager.h"
#include <log/log.h>
#include "system_layer/system_layer_stack.h"
#include <fretbuzz.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class  System
		{
		private:
			//Singleton instance pointer
			static System* s_pInstance;

			System(GameStartup& a_GameStartupData);

			//Initializes the system, is called only once on startup
			static bool isInitialized(GameStartup& a_GameStartupData);

			//Destroys components if failed to initialize and provides cleanup
			static void destroy();

			AudioEngine* m_pAudioEngine = nullptr;

			ns_graphics::MasterRenderer* m_pMasterRenderer = nullptr;

			Input* m_pInput = nullptr;

			//Main resource manager
			ResourceManager* m_pResourceManager = nullptr;

			PhysicsEngine* m_pPhysicsEngine = nullptr;

			LayerManager* m_pLayerManager = nullptr;

			SceneManager* m_pSceneManager = nullptr;

			ns_graphics::FontManager* m_pFontManager = nullptr;

			Log* m_pLog = nullptr;

			EventManager* m_pEventManager = nullptr;

			ns_graphics::Window* m_pWindow = nullptr;

			SystemLayerStack* m_pSystemLayerStack = nullptr;

#if _DEBUG
			ns_fretBuzz::ns_editor::Inspector* m_pInspector = nullptr;
#endif

			bool m_bIsSystemPaused = false;

			float m_fDeltaTime = 0.0f;

			float m_fUnscaledTime = 0.0f;

			//The delta time is scaled to this value between 0 - 1
			float m_fScaledTime = 1.0f;

		public:
			static constexpr float PHYSICS_TIME_STEP = 1.0f / 300.0f;
			~System();

			//Runs the main loop, initializes system publicly if not previusly initialized
			static void run(GameStartup& a_GameStartupData);
			static void close();

			static void SetScaledTime(float a_fScaledTime);
			static const float& GetScaledTime();
			static const float& GetUnscaledTime();
			static const float& GetDeltaTime();
			static bool IsSystemPaused();
			static void ToggleSystemPause(bool a_bisPause);
		};
	}
}