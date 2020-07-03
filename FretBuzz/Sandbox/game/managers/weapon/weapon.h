#pragma once
#include <components/gameobject_components/behaviour.h>
#include <components/gameobject_components/rect_collider.h>
#include <components/gameobject_components/sprite_renderer.h>
#include "game/managers/weapon/weapon_data.h"

namespace ns_HMGame
{
	enum WEAPON_TYPE
	{
		WEAPON_UNARMED = 0,
		WEAPON_GOLF_CLUB = 1,
		WEAPON_PIPE = 2,
		WEAPON_BAT = 3,
		WEAPON_KNIFE = 4,
		WEAPON_M16 = 5,
		WEAPON_SHOTGUN = 6,
		WEAPON_DOUBLE_BARREL = 7,
		WEAPON_KATANA = 8,
		WEAPON_BOTTLE = 9,
		WEAPON_MAGNUM = 10,
		WEAPON_MACHETE = 11,
		WEAPON_CAN = 12,
		WEAPON_SUBMACHINE = 13,
		WEAPON_HAMMER = 14,
		WEAPON_SHURIKEN = 15,
		WEAPON_DART = 16,
		WEAPON_MP5 = 17,
		WEAPON_AXE = 18,
		WEAPON_SCISSORS = 19,
		WEAPON_SILENCER = 20,
		WEAPON_UZI = 21,
		WEAPON_BRICK = 22
	};

	class Weapon : public ns_fretBuzz::Behaviour
	{
	private:
		ns_fretBuzz::SpriteRenderer* m_pSpriteRenderer = nullptr;
		ns_fretBuzz::Collider2D* m_pCollider2D = nullptr;

		WeaponData m_WeaponData;

		enum WEAPON_STATE
		{
			DROP,
			IN_USE,
			THROWN
		};

		WEAPON_STATE m_CurrentWeaponState;
		void setWeaponState(WEAPON_STATE a_State);

	public:
		Weapon(ns_fretBuzz::GameObject2D* a_GameObject);
		WeaponData getWeaponData();

		void setWeapon(WEAPON_TYPE a_WeaponType);
		virtual void onTriggerEnter2D(ns_fretBuzz::Collider2D* a_pIComponent) override;
		virtual void onTriggerExit2D(ns_fretBuzz::Collider2D* a_pIComponent) override;
		virtual void onCollisionEnter2D(ns_fretBuzz::Collider2D* a_pIComponent) override;
		virtual void onCollisionExit2D(ns_fretBuzz::Collider2D* a_pIComponent) override;

		void startWeaponThrow(glm::vec2 a_v2PlayerToMouseDirection);
		void pickup();

		virtual void update(const float& a_fDeltaTime) override;

		void fire(glm::vec3 a_v3Position, glm::vec3 a_v3Direction);
	};
}