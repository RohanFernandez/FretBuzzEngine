#pragma once
#include "../system/core/resource_manager.h"
#include "../components/sprite.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class FRETBUZZ_API AnimationState
		{
		private:
			std::string m_strStateId;
			ns_graphics::SpriteGroup* m_pSpriteGroup = nullptr;
			bool m_bIsLoop = false;
			float m_fTimePerSprite = 0.0f;
			std::map<std::string, std::string> m_mapTrigger;
			std::string m_strOnCompleteTrigger;

		public:
			AnimationState(std::string a_strStateId, std::string a_strSpriteSheetId, bool a_bIsLoop,
				float a_fTimePerSprite, std::map<std::string, std::string> a_mapTrigger, std::string a_strOnCompleteTrigger = "")
				: m_strStateId(a_strStateId),
				m_pSpriteGroup(ResourceManager::getResource<ns_graphics::SpriteGroup>(a_strSpriteSheetId)),
				m_bIsLoop(a_bIsLoop),
				m_fTimePerSprite(a_fTimePerSprite),
				m_mapTrigger(a_mapTrigger),
				m_strOnCompleteTrigger{ a_strOnCompleteTrigger }
			{
				
			}

			AnimationState(AnimationState& a_AnimationState)
				: m_strStateId(a_AnimationState.m_strStateId),
				m_pSpriteGroup(a_AnimationState.m_pSpriteGroup),
				m_bIsLoop(a_AnimationState.m_bIsLoop),
				m_fTimePerSprite(a_AnimationState.m_fTimePerSprite),
				m_mapTrigger(a_AnimationState.m_mapTrigger),
				m_strOnCompleteTrigger(a_AnimationState.m_strOnCompleteTrigger)
			{
				
			}

			AnimationState(AnimationState&& a_AnimationState)
				: m_strStateId(a_AnimationState.m_strStateId),
				m_pSpriteGroup(a_AnimationState.m_pSpriteGroup),
				m_bIsLoop(a_AnimationState.m_bIsLoop),
				m_fTimePerSprite(a_AnimationState.m_fTimePerSprite),
				m_mapTrigger(a_AnimationState.m_mapTrigger),
				m_strOnCompleteTrigger(a_AnimationState.m_strOnCompleteTrigger)
			{

			}

			void operator=(AnimationState a_AnimationState)
			{
				m_strStateId = a_AnimationState.m_strStateId;
				m_pSpriteGroup = a_AnimationState.m_pSpriteGroup;
				m_bIsLoop = a_AnimationState.m_bIsLoop;
				m_fTimePerSprite = a_AnimationState.m_fTimePerSprite;
				m_mapTrigger = a_AnimationState.m_mapTrigger;
				m_strOnCompleteTrigger = a_AnimationState.m_strOnCompleteTrigger;
			}

			~AnimationState()
			{}

			inline std::string getStateId() const
			{
				return m_strStateId;
			}

			inline ns_graphics::SpriteGroup* getSpriteGroup() const
			{
				return m_pSpriteGroup;
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

			inline std::string getOnCompleteTrigger() const
			{
				return m_strOnCompleteTrigger;
			}
		};


		class SpriteAnimator : public ns_system::IManagedResource
		{
		protected:
			std::string m_strAnimControllerId;
			std::vector<AnimationState> m_vectAnimationStates;

			virtual void destroyResource() override;

		public:
			SpriteAnimator() = delete;
			SpriteAnimator(std::string a_strAnimControllerId, std::vector<AnimationState> a_vectAnimStates);
			SpriteAnimator(SpriteAnimator& a_SpriteAnimationController);
			SpriteAnimator(SpriteAnimator&& a_SpriteAnimationController);

			void operator=(SpriteAnimator a_SpriteAnimationController);

			virtual ~SpriteAnimator();

			inline std::vector<AnimationState>& getAnimStates()
			{
				return m_vectAnimationStates;
			}

			AnimationState* getAnimStateWithID(std::string a_strAnimStateID);
		};
	}
}