#include <fretbuzz_pch.h>
#include "weapon_data.h"
#include "weapon_manager.h"

namespace ns_HMGame
{
	//singleton instance
	WeaponManager* WeaponManager::s_pInstance = nullptr;

	WeaponManager::WeaponManager(ns_fretBuzz::ns_system::GameObject* a_GameObject)
		: ns_fretBuzz::ns_system::Behaviour(a_GameObject),
		m_WeaponPool(0, a_GameObject)
	{
		if (s_pInstance != nullptr)
		{
			return;
		}
		s_pInstance = this;

		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED,		"unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_GOLF_CLUB,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_GOLF_CLUB,	"") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_PIPE,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_PIPE,			"pipeidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_BAT,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_BAT,			"batidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_KNIFE,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_KNIFE,		"knifeidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_M16,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::GUN,	  WEAPON_TYPE::WEAPON_M16,			"m16idle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_SHOTGUN,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::GUN,	  WEAPON_TYPE::WEAPON_SHOTGUN,		"") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_DOUBLE_BARREL, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::GUN,   WEAPON_TYPE::WEAPON_DOUBLE_BARREL,  "doublebarrelidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_KATANA,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_KATANA,		"") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_BOTTLE,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::GUN,   WEAPON_TYPE::WEAPON_BOTTLE,		"") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_MAGNUM,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::GUN,	  WEAPON_TYPE::WEAPON_MAGNUM,		"magnumidle") });

		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_MACHETE,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_MACHETE,		"unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_CAN,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_CAN,			"unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_SUBMACHINE,	WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_SUBMACHINE,	"unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_HAMMER,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_HAMMER,		"unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_SHURIKEN,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_SHURIKEN,		"unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_DART,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_DART,			"unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_MP5,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_MP5,			"unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_AXE,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_AXE,			"unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_SCISSORS,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_SCISSORS,		"unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_SILENCER,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_SILENCER,		"unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UZI,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UZI,			"unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_BRICK,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_BRICK,			"unarmedidle") });
		
	}

	WeaponManager::~WeaponManager()
	{
		if (s_pInstance == this)
		{
			s_pInstance = nullptr;
		}
	}

	Weapon* WeaponManager::AddWeapon(glm::vec3 a_v3Position, WEAPON_TYPE a_WeaponType)
	{
		PrefabWeapon* l_pWeaponPrefab = s_pInstance->m_WeaponPool.getGameObject(&s_pInstance->m_GameObject);
		l_pWeaponPrefab->setAsParent(&s_pInstance->m_GameObject);
		l_pWeaponPrefab->m_Transform.setWorldPosition(a_v3Position);
		
		l_pWeaponPrefab->setActive(true);
		Weapon* l_pWeapon = l_pWeaponPrefab->getComponent<Weapon>(ns_fretBuzz::ns_system::COMPONENT_TYPE::BEHAVIOUR);
		l_pWeapon->setWeapon(a_WeaponType);
		return l_pWeapon;
	}
}