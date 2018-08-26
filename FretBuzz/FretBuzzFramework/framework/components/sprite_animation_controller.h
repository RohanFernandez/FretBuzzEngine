#pragma once
#include <string>
#include <vector>
#include <map>
#include "../system/core/resource_manager.h"
#include "../components/sprite.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class AnimationState
		{
		private:
			std::string m_strStateId;
			ns_graphics::SpriteSheet* m_pSpriteSheet = nullptr;
			bool m_bIsLoop = false;
			float m_fTimePerSprite = 0.0f;
			std::map<std::string, std::string> m_mapTrigger;

		public:
			AnimationState(std::string a_strStateId, std::string a_strSpriteSheetId, bool a_bIsLoop,
				float a_fTimePerSprite, std::map<std::string, std::string> a_mapTrigger)
				: m_strStateId(a_strStateId),
				m_pSpriteSheet(ResourceManager::getResource<ns_graphics::SpriteSheet>(a_strSpriteSheetId)),
				m_bIsLoop(a_bIsLoop),
				m_fTimePerSprite(a_fTimePerSprite),
				m_mapTrigger(a_mapTrigger)
			{
				
			}

			AnimationState(AnimationState& a_AnimationState)
				: m_strStateId(a_AnimationState.m_strStateId),
				m_pSpriteSheet(a_AnimationState.m_pSpriteSheet),
				m_bIsLoop(a_AnimationState.m_bIsLoop),
				m_fTimePerSprite(a_AnimationState.m_fTimePerSprite),
				m_mapTrigger(a_AnimationState.m_mapTrigger)
			{
				
			}

			AnimationState(AnimationState&& a_AnimationState)
				: m_strStateId(a_AnimationState.m_strStateId),
				m_pSpriteSheet(a_AnimationState.m_pSpriteSheet),
				m_bIsLoop(a_AnimationState.m_bIsLoop),
				m_fTimePerSprite(a_AnimationState.m_fTimePerSprite),
				m_mapTrigger(a_AnimationState.m_mapTrigger)
			{

			}

			void operator=(AnimationState a_AnimationState)
			{
				m_strStateId = a_AnimationState.m_strStateId;
				m_pSpriteSheet = a_AnimationState.m_pSpriteSheet;
				m_bIsLoop = a_AnimationState.m_bIsLoop;
				m_fTimePerSprite = a_AnimationState.m_fTimePerSprite;
				m_mapTrigger = a_AnimationState.m_mapTrigger;
			}

			~AnimationState()
			{}

			inline std::string getStateId() const
			{
				return m_strStateId;
			}

			inline ns_graphics::SpriteSheet* getSpriteSheet() const
			{
				return m_pSpriteSheet;
			}

			inline bool isLooped() const
			{
				return m_bIsLoop;
			}
			
			inline float getTimePerSprite() const
			{
				return m_fTimePerSprite;
			}

			inline std::map<std::string, std::string> getMapTriggers() const
			{
				return m_mapTrigger;
			}
		};


		class SpriteAnimationController : public ns_system::IManagedResource
		{
		protected:
			std::string m_strAnimControllerId;
			std::vector<AnimationState> m_vectAnimationStates;

			virtual void destroyResource() override;

		public:
			SpriteAnimationController() = delete;
			SpriteAnimationController(std::string a_strAnimControllerId, std::vector<AnimationState> a_vectAnimStates);
			SpriteAnimationController(SpriteAnimationController& a_SpriteAnimationController);
			SpriteAnimationController(SpriteAnimationController&& a_SpriteAnimationController);

			void operator=(SpriteAnimationController a_SpriteAnimationController);

			virtual ~SpriteAnimationController();

			inline std::vector<AnimationState>& getAnimStates()
			{
				return m_vectAnimationStates;
			}

			AnimationState* getAnimStateWithID(std::string a_strAnimStateID);
		};
	}
}