#pragma once
#include "system/component.h"

namespace FRETBUZZ
{
	class GameObject;
	class  CharacterController2D : public IComponent
	{
	private:

	protected:
		virtual ~CharacterController2D();

	public:
		CharacterController2D(GameObject* a_GameObject);
	};
}