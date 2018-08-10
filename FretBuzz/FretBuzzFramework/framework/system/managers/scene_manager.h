#pragma once
#include "../../components/FSM.h"
#include <type_traits>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//Each scene state should be inherited from IScene
		class IScene : public IFSM
		{
		public:
			IScene() = delete;

			virtual ~IScene() = 0
			{}

		protected:
			IScene(std::string a_strSceneName) 
				: IFSM(a_strSceneName)
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

			virtual bool isSceneActive() = 0;

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

		public:
			SceneData() = delete;

			SceneData(std::string a_strSceneID)
				: ISceneData(a_strSceneID)
			{

			}

			virtual ~SceneData()
			{

			}

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
			virtual bool isSceneActive() override
			{
				return (m_pScene != nullptr);
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

			SceneManager(ISceneData* a_pStartScene);
			SceneManager(std::vector<ISceneData*>& a_pVectIScene);

			virtual ~SceneManager();

			void registerState(ISceneData* a_pScene);

			void loadScene(std::string a_strSceneName, LoadSceneMode a_LoadSceneMode = Single);
			void unloadScene(std::string a_strSceneName);
			
			void logAllActiveSceneNames();

		protected:
			virtual void transitionTo(std::string a_strTransitionTo) override;

		private:
			LoadSceneMode m_CurrentLoadSceneMode = Single;

			///States added additively which includes the current state
			std::vector<ISceneData*> m_vectActiveStates;

			void unloadAllScenes();

		};
	}
}