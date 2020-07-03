#pragma once
#include <components/gameobject_components/behaviour.h>
#include "components/gameobject_components/sprite_animation_controller.h"
#include <components/gameobject_components/rect_collider.h>
#include <game/managers/weapon/weapon_data.h>
#include <game/managers/weapon/weapon.h>

namespace ns_HMGame
{
	class PlayerControllerHM : public ns_fretBuzz::Behaviour
	{
	private:
		static PlayerControllerHM* s_Instance;

		double m_dMouseX = 0.0;
		double m_dMouseY = 0.0;

		float m_fVelocity = 400.0f;

		bool m_bIsRunning = false;

		ns_fretBuzz::SpriteAnimationController* m_pUpperSpriteAnimator = nullptr;
		ns_fretBuzz::SpriteAnimationController* m_pLegsSpriteAnimator = nullptr;
		
		ns_fretBuzz::RectCollider* m_pRectCollider = nullptr;

		ns_fretBuzz::GameObject* m_pCamGameObj = nullptr;
		ns_fretBuzz::GameObject* m_pPlayerUpperGameObj = nullptr;
		ns_fretBuzz::GameObject* m_pGameObjCharacterLegs = nullptr;
		void manageInput(float a_fDeltaTime);

		std::vector<Weapon*> m_vectWeaponOver;

		WeaponData m_WeaponData;

		int m_iWeaponOverCount = 0;

		void addToWeaponOver(Weapon* a_Weapon);
		void removeFromWeaponOver(Weapon* a_Weapon);

	public:
		PlayerControllerHM(ns_fretBuzz::GameObject* a_GameObject, ns_fretBuzz::GameObject* a_pCamGameObject, ns_fretBuzz::GameObject* a_pPlayerUpperGameObj, ns_fretBuzz::GameObject* a_pLegsGameObject);

		virtual void update(const float& a_fDeltaTime) override;

		const WeaponData getWeaponData() const { return m_WeaponData; };

		void setAsCurrentWeaponOver(Weapon* a_pWeapon, bool a_bIsOver);

		virtual void onCollisionEnter2D(ns_fretBuzz::Collider2D* a_pICollider2D) override ;
		virtual void onCollisionExit2D (ns_fretBuzz::Collider2D* a_pICollider2D) override ;
		virtual void onTriggerEnter2D  (ns_fretBuzz::Collider2D* a_pICollider2D) override ;
		virtual void onTriggerExit2D   (ns_fretBuzz::Collider2D* a_pICollider2D) override ;

		inline static PlayerControllerHM* GetInstance()
		{
			return s_Instance;
		}
	};
}