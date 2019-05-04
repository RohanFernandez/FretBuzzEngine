#pragma once
#include <components/gameobject_components/behaviour.h>
#include <components/gameobject_components/rect_collider.h>
#include <components/gameobject_components/sprite_renderer.h>

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

	class Weapon : public ns_fretBuzz::ns_system::Behaviour
	{
	private:
		WEAPON_TYPE m_WeaponType = WEAPON_TYPE::WEAPON_UNARMED;
		ns_fretBuzz::ns_graphics::SpriteRenderer* m_pSpriteRenderer = nullptr;

	public:
		Weapon(ns_fretBuzz::ns_system::GameObject2D* a_GameObject);
		void setWeapon(WEAPON_TYPE a_WeaponType);
		virtual void onTriggerEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent) override;
		virtual void onTriggerExit2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent) override;
	};
}