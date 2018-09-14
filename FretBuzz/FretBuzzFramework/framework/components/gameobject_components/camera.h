#pragma once
#include "../../system/component.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class GameObject;
		class Camera : public IComponent
		{
		private:
			Camera(GameObject& a_GameObj, Viewport& a_Viewport);

		protected:
			virtual ~Camera();

		public:
			static Camera* addToGameObject(GameObject& a_GameObj, Viewport& a_Viewport);
		};
	}
}