#pragma once
#include <string>

namespace ns_HMGame
{
	enum WEAPON_TYPE;
	class WeaponData
	{
	public:
		enum WEAPON_ATTACK_TYPE
		{
			MELEE = 0,
			GUN = 1
		};

		WeaponData(WEAPON_ATTACK_TYPE a_WeaponAttackType, WEAPON_TYPE a_WeaponType, std::string a_strAnimOverrideTrigger);
		~WeaponData();

		WEAPON_TYPE getWeaponType() const;
		WEAPON_ATTACK_TYPE getWeaponAttackType() const;
		std::string getWeaponAnimTrigger() const;

	private:
		WEAPON_TYPE m_WeaponType;
		WEAPON_ATTACK_TYPE m_WeaponAttackType;
		std::string m_strAnimOverrideTrigger;
	};
}