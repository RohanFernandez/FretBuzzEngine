#pragma once
#include <components/gameobject_components/behaviour.h>
#include <components/gameobject_components/rect_collider.h>
#include <components/gameobject_components/sprite_renderer.h>

namespace ns_HMGame
{
	enum WEAPON_TYPE;
	class Weapon : public ns_fretBuzz::ns_system::Behaviour
	{
	private:
		WEAPON_TYPE m_WeaponType;
		ns_fretBuzz::ns_graphics::SpriteRenderer* m_pSpriteRenderer = nullptr;

	public:
		Weapon(ns_fretBuzz::ns_system::GameObject2D& a_GameObject);
		void setWeapon(WEAPON_TYPE a_WeaponType);
		virtual void onTriggerEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent) override;
		virtual void onTriggerExit2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent) override;
	};
}