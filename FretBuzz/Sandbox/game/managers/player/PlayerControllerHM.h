#pragma once
#include <components/gameobject_components/behaviour.h>
#include "components/gameobject_components/sprite_animation_controller.h"
#include <components/gameobject_components/rect_collider.h>
#include <game/managers/weapon/weapon_data.h>
#include <game/managers/weapon/weapon.h>
#include <framework\components\gameobject_components\audio_source.h>

namespace ns_HMGame
{
	class PlayerControllerHM : public FRETBUZZ::Behaviour
	{
	private:
		static PlayerControllerHM* s_Instance;

		double m_dMouseX = 0.0;
		double m_dMouseY = 0.0;

		float m_fVelocity = 600.0f;

		bool m_bIsRunning = false;

		FRETBUZZ::SpriteAnimationController* m_pUpperSpriteAnimator = nullptr;
		FRETBUZZ::SpriteAnimationController* m_pLegsSpriteAnimator = nullptr;
		
		FRETBUZZ::RectCollider* m_pRectCollider = nullptr;

		FRETBUZZ::GameObject* m_pCamGameObj = nullptr;
		FRETBUZZ::GameObject* m_pPlayerUpperGameObj = nullptr;
		FRETBUZZ::GameObject* m_pGameObjCharacterLegs = nullptr;
		void manageInput(float a_fDeltaTime);

		std::vector<Weapon*> m_vectWeaponOver;

		WeaponData m_WeaponData;

		FRETBUZZ::AudioSource* m_pPlayerAudSrc = nullptr;

		int m_iWeaponOverCount = 0;

		void addToWeaponOver(Weapon* a_Weapon);
		void removeFromWeaponOver(Weapon* a_Weapon);

	public:
		PlayerControllerHM(FRETBUZZ::GameObject* a_GameObject, FRETBUZZ::GameObject* a_pCamGameObject, FRETBUZZ::GameObject* a_pPlayerUpperGameObj, FRETBUZZ::GameObject* a_pLegsGameObject);

		virtual void update(const float& a_fDeltaTime) override;

		const WeaponData getWeaponData() const { return m_WeaponData; };

		void setAsCurrentWeaponOver(Weapon* a_pWeapon, bool a_bIsOver);

		virtual void onCollisionEnter2D(FRETBUZZ::Collider2D* a_pICollider2D) override ;
		virtual void onCollisionExit2D (FRETBUZZ::Collider2D* a_pICollider2D) override ;
		virtual void onTriggerEnter2D  (FRETBUZZ::Collider2D* a_pICollider2D) override ;
		virtual void onTriggerExit2D   (FRETBUZZ::Collider2D* a_pICollider2D) override ;

		inline static PlayerControllerHM* GetInstance()
		{
			return s_Instance;
		}
	};
}