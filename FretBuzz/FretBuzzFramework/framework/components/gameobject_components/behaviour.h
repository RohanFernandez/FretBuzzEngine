#pragma once
#include "system/component.h"
#include "system/component_2d.h"
#include <cstdarg>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class GameObject;
		class  Behaviour : public IComponent
		{
		protected:
			Behaviour() = delete;

		protected:
			virtual ~Behaviour(){};

			virtual void update(const float& a_fDeltaTime) override {};
			virtual void render(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera) override {};

		public:

			Behaviour(GameObject* a_GameObject)
				: IComponent(COMPONENT_TYPE::BEHAVIOUR, a_GameObject)
			{

			}
		};
	}
}