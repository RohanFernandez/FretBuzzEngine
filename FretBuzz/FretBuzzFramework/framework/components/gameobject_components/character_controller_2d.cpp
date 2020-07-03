#include <fretbuzz_pch.h>
#include "character_controller_2d.h"
#include "system/game_object.h"

namespace ns_fretBuzz
{
	CharacterController2D::CharacterController2D(GameObject* a_GameObject)
		: IComponent(COMPONENT_TYPE::CHARACTER_CONTROLLER_2D, a_GameObject)
	{
		
	}


	CharacterController2D::~CharacterController2D()
	{
		
	}
}