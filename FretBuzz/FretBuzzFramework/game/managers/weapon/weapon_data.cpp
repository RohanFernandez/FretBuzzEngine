#include <fretbuzz_pch.h>
#include "weapon_manager.h"
#include "weapon_data.h"

namespace ns_HMGame
{
	WeaponData::WeaponData(WEAPON_ATTACK_TYPE a_WeaponAttackType, WEAPON_TYPE a_WeaponType, std::string a_strAnimOverrideTrigger)
		:	m_WeaponAttackType{ a_WeaponAttackType },
			m_WeaponType{a_WeaponType},
			m_strAnimOverrideTrigger{ a_strAnimOverrideTrigger }
	{
		
	}

	WeaponData::~WeaponData()
	{
		
	}

	WEAPON_TYPE WeaponData::getWeaponType() const
	{
		return m_WeaponType;
	}

	WeaponData::WEAPON_ATTACK_TYPE WeaponData::getWeaponAttackType() const
	{
		return m_WeaponAttackType;
	}

	std::string WeaponData::getWeaponAnimTrigger() const
	{
		return m_strAnimOverrideTrigger;
	}
}