#pragma once
#include <components/gameobject_components/behaviour.h>
#include "weapon.h"
#include <utils/pool/gameobject_pool.h>
#include <game/prefab/prefab_weapon.h>

namespace ns_HMGame
{
	class WeaponData;
	class WeaponManager : public ns_fretBuzz::ns_system::Behaviour
	{
	private:
		static WeaponManager* s_pInstance;
		std::map<WEAPON_TYPE, WeaponData> m_WeaponMap;

		ns_fretBuzz::GameObjectPool<PrefabWeapon, ns_fretBuzz::ns_system::GameObject*> m_WeaponPool;

	protected:
		virtual ~WeaponManager();

	public:
		WeaponManager(ns_fretBuzz::ns_system::GameObject* a_GameObject);

		static Weapon* AddWeapon(glm::vec3 a_v3Position, WEAPON_TYPE a_WeaponType);
	};
}