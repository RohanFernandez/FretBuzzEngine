#include <fretbuzz_pch.h>
#include "weapon_data.h"
#include "weapon_manager.h"

namespace ns_HMGame
{
	//singleton instance
	WeaponManager* WeaponManager::s_pInstance = nullptr;

	WeaponManager::WeaponManager(FRETBUZZ::GameObject* a_GameObject)
		: FRETBUZZ::Behaviour(a_GameObject),
		m_WeaponPool(),
		m_BulletPool()
	{
		if (s_pInstance != nullptr)
		{
			return;
		}
		s_pInstance = this;

		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UNARMED,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UNARMED,		"unarmedidle"			, ""									,"") });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_GOLF_CLUB,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_GOLF_CLUB,	""						, "weapon_pickup|weapon_golf_club"		,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_PIPE,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_PIPE,			"pipeidle"				, "weapon_pickup|weapon_pipe"			,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_BAT,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_BAT,			"batidle"				, "weapon_pickup|weapon_bat"			,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_KNIFE,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_KNIFE,		"knifeidle"				, "weapon_pickup|weapon_knife"			,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_M16,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::GUN,	  WEAPON_TYPE::WEAPON_M16,			"m16idle"				, "weapon_pickup|weapon_M16"			,"weapon_pickup|bullet_m16" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_SHOTGUN,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::GUN,	  WEAPON_TYPE::WEAPON_SHOTGUN,		""						, "weapon_pickup|weapon_shotgun"		,"weapon_pickup|bullet_shotgun" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_DOUBLE_BARREL, WeaponData(WeaponData::WEAPON_ATTACK_TYPE::GUN,   WEAPON_TYPE::WEAPON_DOUBLE_BARREL,  "doublebarrelidle"	, "weapon_pickup|weapon_doublebarrel"	,"weapon_pickup|bullet_shotgun" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_KATANA,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_KATANA,		""						, "weapon_pickup|weapon_katana"			,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_BOTTLE,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::GUN,   WEAPON_TYPE::WEAPON_BOTTLE,		""						, "weapon_pickup|weapon_bottle"			,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_MAGNUM,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::GUN,	  WEAPON_TYPE::WEAPON_MAGNUM,		"magnumidle"			, "weapon_pickup|weapon_magnum"			,"weapon_pickup|bullet_shotgun" ) });
																																																					 
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_MACHETE,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_MACHETE,		"unarmedidle" ,""												,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_CAN,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_CAN,			"unarmedidle" ,""												,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_SUBMACHINE,	WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_SUBMACHINE,	"unarmedidle" ,""												,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_HAMMER,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_HAMMER,		"unarmedidle" ,""												,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_SHURIKEN,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_SHURIKEN,		"unarmedidle" ,""												,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_DART,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_DART,			"unarmedidle" ,""												,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_MP5,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_MP5,			"unarmedidle" ,""												,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_AXE,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_AXE,			"unarmedidle" ,""												,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_SCISSORS,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_SCISSORS,		"unarmedidle" ,""												,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_SILENCER,		WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_SILENCER,		"unarmedidle" ,""												,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_UZI,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_UZI,			"unarmedidle" ,""												,"" ) });
		m_WeaponMap.insert({ WEAPON_TYPE::WEAPON_BRICK,			WeaponData(WeaponData::WEAPON_ATTACK_TYPE::MELEE, WEAPON_TYPE::WEAPON_BRICK,		"unarmedidle" ,""												,"" ) });
		
	}

	WeaponManager::~WeaponManager()
	{
		if (s_pInstance == this)
		{
			s_pInstance = nullptr;
		}
	}

	WeaponData WeaponManager::GetWeaponData(WEAPON_TYPE a_WeaponType)
	{
		return s_pInstance->m_WeaponMap.find(a_WeaponType)->second;
	}

	Weapon* WeaponManager::AddWeapon(glm::vec3 a_v3Position, WEAPON_TYPE a_WeaponType, bool a_bIsActive)
	{
		PrefabWeapon* l_pWeaponPrefab = s_pInstance->m_WeaponPool.getGameObject(&s_pInstance->m_GameObject);
		l_pWeaponPrefab->setAsParent(&s_pInstance->m_GameObject);
		l_pWeaponPrefab->m_Transform.setWorldPosition(a_v3Position);
		
		l_pWeaponPrefab->setActive(a_bIsActive);
		Weapon* l_pWeapon = l_pWeaponPrefab->getComponent<Weapon>(FRETBUZZ::COMPONENT_TYPE::BEHAVIOUR);
		l_pWeapon->setWeapon(a_WeaponType);
		return l_pWeapon;
	}

	Bullet* WeaponManager::AddBullet(glm::vec2 a_v2Position, glm::quat a_quatRotation, std::string a_strBulletSpriteName)
	{
		PrefabBullet* l_pPrefabBullet = s_pInstance->m_BulletPool.getGameObject(&s_pInstance->m_GameObject);
		l_pPrefabBullet->setAsParent(&s_pInstance->m_GameObject);
		l_pPrefabBullet->m_Transform.setLocalRotation(a_quatRotation);
		l_pPrefabBullet->m_Transform.setWorldPosition(glm::vec3{a_v2Position,0.0f});
		l_pPrefabBullet->setActive(true);
		Bullet* l_pBullet = l_pPrefabBullet->getComponent<Bullet>(FRETBUZZ::COMPONENT_TYPE::BEHAVIOUR);
		l_pBullet->setBulletType(a_strBulletSpriteName);

		return l_pBullet;
	}

	void WeaponManager::ReturnWeaponToPool(PrefabWeapon* a_pWeaponToReturn)
	{
		s_pInstance->m_WeaponPool.returnToPool(a_pWeaponToReturn);
	}

	void WeaponManager::ReturnBulletToPool(PrefabBullet* a_pWeaponToReturn)
	{
		s_pInstance->m_BulletPool.returnToPool(a_pWeaponToReturn);
	}
}