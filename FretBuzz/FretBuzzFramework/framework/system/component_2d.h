#pragma once
#include "component.h"
#include "game_object_2d.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class  IComponent2D : public IComponent
		{
		public:
			IComponent2D(const COMPONENT_TYPE a_ComponentType, GameObject2D* a_GameObj, bool a_bIsEnabled = true)
				: IComponent(a_ComponentType, a_GameObj, a_bIsEnabled),
				m_GameObject2D{ *a_GameObj }
			{

			}

			virtual ~IComponent2D() = 0
			{
			}

			GameObject2D& m_GameObject2D;

		protected:
			// Event called when the GameObject is activated.
			virtual void onEnable() override 
			{
				IComponent::onEnable();
			}

			// Event called when the GameObject is deactivated.
			virtual void onDisable() override 
			{
				IComponent::onDisable();
			}
		};

		
	}
}