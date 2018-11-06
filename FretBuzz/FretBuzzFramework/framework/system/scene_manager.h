#pragma once
#include "../utils/FSM.h"
#include "game_object.h"
#include "../components/gameobject_components/camera.h"
#include <type_traits>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//Each scene state should be inherited from IScene
		class IScene : public IFSM
		{

		private:
			GameObject* m_pGameObjectRoot = nullptr;

		public:
			IScene() = delete;

			virtual void OnStateEnter() override
			{
				IFSM::OnStateEnter();
			}

			virtual void OnStateExit() override
			{
				IFSM::OnStateExit();
			}

			virtual ~IScene()
			{
				delete m_pGameObjectRoot;
				m_pGameObjectRoot = nullptr;
			}

			GameObject& m_refRootGameObject;

			void render(const ns_graphics::Camera& a_Camera)
			{
				m_refRootGameObject.render(a_Camera);
			}

			void update(float a_fDeltaTime)
			{
				m_refRootGameObject.update(a_fDeltaTime);
			}

			void resetDontDestroyParentTo(IScene* a_IScene)
			{
				m_pGameObjectRoot->resetDontDestroyParent(a_IScene->m_refRootGameObject);
			}

			void logHierarchy()
			{
				std::cout << "\n\nSCENE:: " << m_strStateName << "\n\t";
				m_refRootGameObject.logHierarchy(1);
				std::cout << "\n\n";
			}

		protected:
			IScene(std::string a_strSceneName) 
				: IFSM(a_strSceneName),
				m_pGameObjectRoot{ new GameObject(a_strSceneName + "::ROOT")},
				m_refRootGameObject{ *m_pGameObjectRoot }
			{
			}
		};

		//The SceneData is inherited from this for the scene management,
		//mainly to store it as the type of FSM states because scene data is of type and
		//hence cannot be stored in a list
		class ISceneData : public IFSM
		{
		public:
			ISceneData() = delete;

			virtual ~ISceneData() = 0
			{}

			virtual void unloadSceneData() = 0;

			virtual bool isSceneLoaded() = 0;

			virtual void render(const ns_graphics::Camera& a_Camera) = 0;
			virtual void update(float a_fDeltaTime) = 0;

			virtual void resetDontDestroyParent(ISceneData& a_NewSceneParent)
			{}

			virtual IScene* getIScene() = 0;

			virtual void logHierarchy() = 0;

		protected:
			ISceneData(std::string a_strSceneID)
				: IFSM(a_strSceneID)
			{

			}
		};

		//To create a scene state, this a scene state wtih this class should be created with SCENE_TYPE as the Scene State type.
		template<typename SCENE_TYPE, typename = typename std::enable_if<std::is_base_of<IScene, SCENE_TYPE>::value>::type>
		class SceneData : public ISceneData
		{
		private:
			SCENE_TYPE* m_pScene = nullptr;

			virtual IScene* getIScene() override
			{
				return m_pScene;
			}

		public:
			SceneData() = delete;

			SceneData(std::string a_strSceneID)
				: ISceneData(a_strSceneID)
			{

			}

			virtual ~SceneData()
			{}


			//On entering the state it will instantiate the state of type SCENE_TYPE
			virtual void OnStateEnter() override
			{
				//IFSM::OnStateEnter();
				if (m_pScene == nullptr)
				{
					m_pScene = new SCENE_TYPE("SCENE_STATE::" + getStateName());
				}

				IFSM* l_pIFSM = nullptr;
				l_pIFSM = static_cast<IFSM*>(m_pScene);

				if (l_pIFSM != nullptr)
				{
					l_pIFSM->OnStateEnter();
				}
				else
				{
					std::cout <<"SceneManager::OnStateEnter::" << std::string(typeid(SCENE_TYPE).name()) << " cannot be casted to base class ' FretBuzzManager::IFSM* '\n";
				}
			}

			//Deletes the current scene state
			virtual void OnStateExit() override
			{
				//IFSM::OnStateExit();

				IFSM* l_pIFSM = nullptr;
				l_pIFSM = static_cast<IFSM*>(m_pScene);

				if (l_pIFSM != nullptr)
				{
					l_pIFSM->OnStateExit();
				}
				else
				{
					std::cout<<"SceneManager::OnStateExit::" << std::string(typeid(SCENE_TYPE).name()) << " cannot be casted to base class ' FretBuzzManager::IFSM* '\n";
				}
			}

			virtual void resetDontDestroyParent(ISceneData& a_NewSceneParent) override
			{
				m_pScene->resetDontDestroyParentTo(a_NewSceneParent.getIScene());
			}

			void render(const ns_graphics::Camera& a_Camera)
			{
				m_pScene->render(a_Camera);
			}

			void update(float a_fDeltaTime)
			{
				m_pScene->update(a_fDeltaTime);
			}

			///Unloads the scene object, destroys and deletes all data initialize in that scene class.
			virtual void unloadSceneData() override
			{
				if (m_pScene != nullptr)
				{
					delete m_pScene;
					m_pScene = nullptr;
				}
			}

			///Is scene currently in list of active scenes in the manager.
			///Specifies if the scene is currently running.
			virtual bool isSceneLoaded() override
			{
				return (m_pScene != nullptr);
			}

			virtual void logHierarchy() override
			{
				m_pScene->logHierarchy();
			}
		};

		//Specialized class for Scene Managment from FSM, could be template specialize but decided to write it separately
		//The main class for scene management
		class SceneManager : public FSM<ISceneData>
		{
		public:
			enum LoadSceneMode
			{
				Single,
				Additive
			};

			static void s_registerState(ISceneData* a_pScene);
			static void s_loadScene(std::string a_strSceneName, LoadSceneMode a_LoadSceneMode = Single);
			static void s_unloadScene(std::string a_strSceneName);
			static void s_logAllActiveSceneNames();

			void updateActiveScenes(float a_fDeltaTime);
			void renderActiveScenes(const ns_graphics::Camera& a_Camera);

			static void printSceneHierarchy();

			static SceneManager* initialize(std::vector<ISceneData*>& a_pVectIScene);
			static const SceneManager* get();
			void destroy();

		protected:
			SceneManager(ISceneData* a_pStartScene);
			SceneManager(std::vector<ISceneData*>& a_pVectIScene);

			virtual ~SceneManager();
			virtual void transitionTo(std::string a_strTransitionTo) override;

			void registerState(ISceneData* a_pScene);
			void loadScene(std::string a_strSceneName, LoadSceneMode a_LoadSceneMode = Single);
			void unloadScene(std::string a_strSceneName);
			void logAllActiveSceneNames();

		private:
			static SceneManager* s_pInstance;

			LoadSceneMode m_CurrentLoadSceneMode = Single;

			///States added additively which includes the current state
			std::vector<ISceneData*> m_vectActiveStates;

			void unloadAllScenes();
		};
	}
}