#include <fretbuzz_pch.h>
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
	}

	WeaponManager::~WeaponManager()
	{
		if (s_pInstance == this)
		{
			s_pInstance = nullptr;
		}
	}
}