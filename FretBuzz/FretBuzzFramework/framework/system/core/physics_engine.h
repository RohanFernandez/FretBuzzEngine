#pragma once
#include <components/raycast_callback.h>
#include <system/component.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		enum class PHYSICS_BODY_TYPE
		{
			STATIC		= 0,
			KINEMATIC	= 1,
			DYNAMIC		= 2
		};

		struct Collider2DContactEvent
		{
			using T_CONTACT_CALLBACK = void(IComponent::*)(Collider2D*);
			using T_EVENT_TYPE = void(*)(Collider2D*, Collider2D*, T_CONTACT_CALLBACK, T_CONTACT_CALLBACK);

			Collider2D* m_pColliderA = nullptr;
			Collider2D* m_pColliderB = nullptr;
			T_CONTACT_CALLBACK m_pFuncTriggerCallback = nullptr;
			T_CONTACT_CALLBACK m_pFuncCollisionCallback = nullptr;

			T_EVENT_TYPE m_ContactEvent = nullptr;

			void invoke()
			{
				(*m_ContactEvent)(m_pColliderA, m_pColliderB, m_pFuncCollisionCallback, m_pFuncTriggerCallback);
			}
		};

		class  PhysicsEngine
		{
		private:
			static PhysicsEngine* s_pInstance;

			b2World* m_pB2World = nullptr;
			RaycastCallback m_RaycastCallback;

			int m_iVelocityIteration = 0;
			int m_iStepIteration = 0;

			float m_fTimePassedSinceLastStep = 0.0f;

			std::stack<Collider2DContactEvent> m_stackContactEvent;

			void invokeContactCallbacks();

			PhysicsEngine(b2Vec2 a_v2Gravity, int a_iVelocityIteration, int a_iStepIteration);
			~PhysicsEngine();

		public:
			static PhysicsEngine* initialize(b2Vec2 a_v2Gravity, int a_iVelocityIteration, int a_iStepIteration);
			void destroy();
			static const PhysicsEngine* get();

			static b2World* getB2World();

			void step(float a_fDeltaTime);

			static void Raycast(Collider2D*& a_pCollider2D, glm::vec2 a_v2Point1, glm::vec2 a_v2Point2);
			static void AddContactEvent(Collider2DContactEvent a_ContactEvent);
		};
	}
}