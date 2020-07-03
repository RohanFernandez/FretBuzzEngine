#pragma once
#include <components/gameobject_components/behaviour.h>
#include "weapon.h"
#include "game/managers/bullet/bullet.h"
#include <utils/pool/gameobject_pool.h>
#include <game/prefab/prefab_weapon.h>
#include <game/prefab/prefab_bullet.h>

namespace ns_HMGame
{
	class WeaponData;
	class WeaponManager : public ns_fretBuzz::Behaviour
	{
	private:
		static WeaponManager* s_pInstance;
		std::map<WEAPON_TYPE, WeaponData> m_WeaponMap;

		ns_fretBuzz::GameObjectPool<PrefabWeapon> m_WeaponPool;
		ns_fretBuzz::GameObjectPool<PrefabBullet> m_BulletPool;

	protected:
		virtual ~WeaponManager();

	public:
		WeaponManager(ns_fretBuzz::GameObject* a_GameObject);

		static WeaponData GetWeaponData(WEAPON_TYPE a_WeaponType);
		static Weapon* AddWeapon(glm::vec3 a_v3Position, WEAPON_TYPE a_WeaponType, bool a_bIsActiv);
		static void ReturnWeaponToPool(PrefabWeapon* a_pWeaponToReturn);

		static Bullet* AddBullet(glm::vec2 a_v2Position, glm::quat a_quatRotation, std::string a_strBulletSpriteName);
		static void ReturnBulletToPool(PrefabBullet* a_pWeaponToReturn);
	};
}