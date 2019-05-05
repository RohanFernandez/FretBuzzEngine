#include <fretbuzz_pch.h>
#include "weapon_manager.h"
#include "weapon_data.h"

namespace ns_HMGame
{

	WeaponData::WeaponData(WEAPON_TYPE a_WeaponType)
		: WeaponData{WeaponManager::GetWeaponData(a_WeaponType)}
	{
		
	}

	WeaponData::WeaponData(const WeaponData& a_WeaponData)
		: WeaponData{ a_WeaponData.m_WeaponAttackType, a_WeaponData.m_WeaponType, a_WeaponData.m_strAnimOverrideTrigger, a_WeaponData.m_strWeaponSpriteName }
	{

	}

	WeaponData::WeaponData(WEAPON_ATTACK_TYPE a_WeaponAttackType, WEAPON_TYPE a_WeaponType, std::string a_strAnimOverrideTrigger, std::string a_strSpriteName)
		:	m_WeaponAttackType{ a_WeaponAttackType },
			m_WeaponType{a_WeaponType},
			m_strAnimOverrideTrigger{ a_strAnimOverrideTrigger },
			m_strWeaponSpriteName{ a_strSpriteName }
	{
		
	}

	WeaponData::~WeaponData()
	{
		
	}

	void WeaponData::operator=(const WeaponData& a_Other)
	{
		m_WeaponType = a_Other.m_WeaponType;
		m_WeaponAttackType = a_Other.m_WeaponAttackType;
		m_strAnimOverrideTrigger = a_Other.m_strAnimOverrideTrigger;
		m_strWeaponSpriteName = a_Other.m_strWeaponSpriteName;
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

	std::string WeaponData::getWeaponSpriteName() const
	{
		return m_strWeaponSpriteName;
	}
}