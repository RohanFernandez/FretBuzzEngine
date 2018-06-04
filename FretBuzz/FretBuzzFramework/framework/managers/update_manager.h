#pragma once
#include <list>

namespace ns_fretBuzz
{
	namespace ns_manager
	{
		class IFrameUpdateTimer;
		class ILateUpdateTimer;

		class UpdateManager
		{
		private:
			friend class IFrameUpdateTimer;
			friend class ILateUpdateTimer;

			//singleton instance
			static UpdateManager* s_pInstance;

			typedef std::list<IFrameUpdateTimer*> FRAME_UPDATE_CONTAINER;
			typedef std::list<ILateUpdateTimer*> LATE_UPDATE_CONTAINER;

			FRAME_UPDATE_CONTAINER m_listUpdateTimer;
			LATE_UPDATE_CONTAINER m_listLateUpdateTimer;

			static void addFrameUpdateTimer(IFrameUpdateTimer* const &a_pUpdatableObject);
			static void removeFrameUpdateTimer(IFrameUpdateTimer* const &a_pUpdatableObject);

			static void addLateUpdateTimer(ILateUpdateTimer* const &a_pUpdatableObject);
			static void removeLateUpdateTimer(ILateUpdateTimer* const &a_pUpdatableObject);

		public:
			UpdateManager();
			~UpdateManager();

			//Updates all the objects that have been registered for Update with the new delta time
			//Called on start of new frame
			void onUpdateFrame(const float a_fDeltaTimer);

			//Updates all the objects that have been registered for LateUpdate with the new delta time
			//Called after the update has been called
			void onUpdateLateFrame(const float a_fDeltaTimer);

			//Returns the count of the stored objects registered for the frame update.
			int getFrameUpdateObjectCount() const;

			//Returns the count of the stored objects registered for the late update.
			int getLateUpdateObjectCount() const;
		};

#pragma region IUpdate

		class IUpdateBase
		{
		public:
			//If true the update function for this object will be called else not
			bool m_bIsUpdatable = true;

			IUpdateBase(bool a_bIsUpdatable = true)
				:m_bIsUpdatable{ a_bIsUpdatable }
			{
			}

			virtual ~IUpdateBase() = 0
			{

			}
		};

#pragma endregion IUpdate

#pragma region IUpdateTimer

		class IFrameUpdateTimer : public virtual IUpdateBase
		{
		public:

			//The update function that will send the delta time
			virtual void onUpdate(const float a_fDeltaTime) = 0;

			//Constructor registers the class for update in the constructor
			IFrameUpdateTimer(bool a_bIsUpdatable = true)
				: IUpdateBase{ a_bIsUpdatable }
			{
				UpdateManager::addFrameUpdateTimer(this);
			}

			virtual ~IFrameUpdateTimer() = 0
			{
				UpdateManager::removeFrameUpdateTimer(this);
			};
		};

#pragma endregion IUpdateTimer


#pragma region ILateUpdateTimer

		class ILateUpdateTimer : public virtual IUpdateBase
		{
		public:

			//The update function that will send the delta time
			virtual void onLateUpdate(const float a_fDeltaTime) = 0;

			//Constructor registers the class for update in the constructor
			ILateUpdateTimer(bool a_bIsUpdatable = true)
				: IUpdateBase{ a_bIsUpdatable }
			{
				UpdateManager::addLateUpdateTimer(this);
			}

			virtual ~ILateUpdateTimer() = 0
			{
				UpdateManager::removeLateUpdateTimer(this);
			};
		};


#pragma endregion ILateUpdateTimer

#pragma region IUpdateTimer

		class IUpdateTimer : public ILateUpdateTimer, public IFrameUpdateTimer
		{
		public:
			IUpdateTimer(const bool IsUpdatable = true)
				: ILateUpdateTimer{ IsUpdatable },
				IFrameUpdateTimer{ IsUpdatable }
			{

			}

			virtual ~IUpdateTimer() = 0
			{
				
			}
		};

#pragma endregion IUpdateTimer
	}
}