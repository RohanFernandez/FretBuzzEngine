#include <fretbuzz_pch.h>
#include "weapon_data.h"
#include "weapon_manager.h"

namespace ns_HMGame
{
	//singleton instance
	WeaponManager* WeaponManager::s_pInstance = nullptr;

	WeaponManager::WeaponManager(ns_fretBuzz::ns_system::GameObject& a_GameObject)
		: ns_fretBuzz::ns_system::Behaviour(a_GameObject)
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

		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED, "unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED, "unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED, "unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED, "unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED, "unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED, "unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED, "unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED, "unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED, "unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED, "unarmedidle") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED, "unarmedidle") });

	}

	WeaponManager::~WeaponManager()
	{
		if (s_pInstance == this)
		{
			s_pInstance = nullptr;
		}
	}
}