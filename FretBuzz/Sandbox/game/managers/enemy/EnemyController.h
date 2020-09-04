#pragma once
#include <components/gameobject_components/behaviour.h>
#include "components/gameobject_components/sprite_animation_controller.h"
#include <components/gameobject_components/rect_collider.h>
#include <game/managers/weapon/weapon_data.h>
#include <game/managers/weapon/weapon.h>

namespace ns_HMGame
{
	class EnemyController : public FRETBUZZ::Behaviour
	{
	private:
		float m_fVelocity = 700.0f;

		float m_fTimeSinceLastShot = 0.0f;
		static constexpr float MIN_TIME_BETWEEN_GUNSHOT = 0.3f;

		bool m_bIsRunning = false;

		FRETBUZZ::SpriteAnimationController* m_pUpperSpriteAnimator = nullptr;
		FRETBUZZ::SpriteAnimationController* m_pLegsSpriteAnimator = nullptr;

		FRETBUZZ::RectCollider* m_pRectCollider = nullptr;

		FRETBUZZ::GameObject* m_pPlayerUpperGameObj = nullptr;
		FRETBUZZ::GameObject* m_pGameObjCharacterLegs = nullptr;

		std::vector<Weapon*> m_vectWeaponOver;

		WeaponData m_WeaponData;

		int m_iWeaponOverCount = 0;

	public:
		EnemyController(FRETBUZZ::GameObject* a_GameObject, FRETBUZZ::GameObject* a_pPlayerUpperGameObj, FRETBUZZ::GameObject* a_pLegsGameObject);

		virtual void update(const float& a_fDeltaTime) override;

		void manageAI(float a_fDeltaTime);

		const WeaponData getWeaponData() const { return m_WeaponData; };

		/*void setAsCurrentWeaponOver(Weapon* a_pWeapon, bool a_bIsOver);

		virtual void onCollisionEnter2D(FRETBUZZ::Collider2D* a_pICollider2D) override;
		virtual void onCollisionExit2D(FRETBUZZ::Collider2D* a_pICollider2D) override;
		virtual void onTriggerEnter2D(FRETBUZZ::Collider2D* a_pICollider2D) override;
		virtual void onTriggerExit2D(FRETBUZZ::Collider2D* a_pICollider2D) override;*/
	};
}