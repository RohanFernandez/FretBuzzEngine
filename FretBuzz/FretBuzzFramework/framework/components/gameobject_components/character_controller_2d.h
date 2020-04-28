#pragma once
#include "system/component.h"

namespace ns_fretBuzz
{ 
	namespace ns_system
	{
		class GameObject;
		class FRETBUZZ_API CharacterController2D : public IComponent
		{
		private:

		protected:
			virtual ~CharacterController2D();

		public:
			CharacterController2D(GameObject* a_GameObject);
		};
	}
}