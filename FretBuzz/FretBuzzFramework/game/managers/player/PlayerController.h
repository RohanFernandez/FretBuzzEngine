#pragma once
#include <components/gameobject_components/behaviour.h>
#include "components/gameobject_components/sprite_animation_controller.h"
#include <components/gameobject_components/rect_collider.h>
#include <game/managers/weapon/weapon.h>

namespace ns_HMGame
{
	class PlayerController : public ns_fretBuzz::ns_system::Behaviour
	{
	private:
		double m_dMouseX = 0.0;
		double m_dMouseY = 0.0;

		float m_fVelocity = 500.0f;

		bool m_bIsRunning = false;

		ns_fretBuzz::ns_system::SpriteAnimationController* m_pUpperSpriteAnimator = nullptr;
		ns_fretBuzz::ns_system::SpriteAnimationController* m_pLegsSpriteAnimator = nullptr;
		
		ns_fretBuzz::ns_system::RectCollider* m_pRectCollider = nullptr;

		ns_fretBuzz::ns_system::GameObject* m_pCamGameObj = nullptr;
		ns_fretBuzz::ns_system::GameObject* m_pPlayerUpperGameObj = nullptr;
		ns_fretBuzz::ns_system::GameObject* m_pGameObjCharacterLegs = nullptr;
		void manageInput();

		ns_HMGame::Weapon* m_pPlayerOverWeapon = nullptr;;
		int m_iWeaponOverCount = 0;

	public:
		PlayerController(ns_fretBuzz::ns_system::GameObject& a_GameObject, ns_fretBuzz::ns_system::GameObject* a_pCamGameObject, ns_fretBuzz::ns_system::GameObject* a_pPlayerUpperGameObj, ns_fretBuzz::ns_system::GameObject* a_pLegsGameObject);

		virtual void update(float a_fDeltaTime) override;

		void setAsCurrentWeapon(Weapon* a_pWeapon);

		virtual void onCollisionEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pICollider2D) override ;
		virtual void onCollisionExit2D (ns_fretBuzz::ns_system::Collider2D* a_pICollider2D) override ;
		virtual void onTriggerEnter2D  (ns_fretBuzz::ns_system::Collider2D* a_pICollider2D) override ;
		virtual void onTriggerExit2D   (ns_fretBuzz::ns_system::Collider2D* a_pICollider2D) override ;
	};
}