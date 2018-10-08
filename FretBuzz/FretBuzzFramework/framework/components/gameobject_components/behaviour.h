#pragma once
#include "../../system/component.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class GameObject;
		class Behaviour : public IComponent
		{
		protected:
			Behaviour() = delete;

			Behaviour(GameObject& a_GameObject)
				: IComponent(COMPONENT_TYPE::BEHAVIOUR, a_GameObject)
			{
				
			}

		protected:
			virtual ~Behaviour(){};

			virtual void update(float a_fDeltaTime) override {};
			virtual void render(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera) override {};

		public:
			template<typename T_BEHAVIOUR, typename = typename std::enable_if<std::is_base_of<Behaviour, T_BEHAVIOUR>::value>::type>
			static T_BEHAVIOUR* addToGameObject(GameObject& a_GameObject)
			{
				return new T_BEHAVIOUR(a_GameObject);
			}
		};
	}
}