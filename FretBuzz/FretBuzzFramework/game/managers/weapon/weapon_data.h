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

		WeaponData(WEAPON_TYPE a_WeaponType);
		WeaponData(const WeaponData& a_WeaponData);
		WeaponData(WEAPON_ATTACK_TYPE a_WeaponAttackType, WEAPON_TYPE a_WeaponType, std::string a_strAnimOverrideTrigger, std::string a_strSpriteName);
		~WeaponData();

		WEAPON_TYPE getWeaponType() const;
		WEAPON_ATTACK_TYPE getWeaponAttackType() const;
		std::string getWeaponAnimTrigger() const;
		std::string getWeaponSpriteName() const;

		void operator=(const WeaponData& a_Other);

	private:
		WEAPON_TYPE m_WeaponType;
		WEAPON_ATTACK_TYPE m_WeaponAttackType;
		std::string m_strAnimOverrideTrigger;
		std::string m_strWeaponSpriteName;
	};
}