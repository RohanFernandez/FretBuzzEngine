#pragma once
#include <components/gameobject_components/behaviour.h>

namespace ns_HMGame
{
	class WeaponManager : public ns_fretBuzz::ns_system::Behaviour
	{
	private:
		static WeaponManager* s_pInstance;

	protected:
		virtual ~WeaponManager();

	public:
		WeaponManager(ns_fretBuzz::ns_system::GameObject& a_GameObject);
	};
}