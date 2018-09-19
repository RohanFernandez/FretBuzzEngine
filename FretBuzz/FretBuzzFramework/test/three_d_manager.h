#pragma once

#pragma once

#include "../framework/system/game_object_2d.h" 
#include "../framework/components/gameobject_components/audio_source.h"
#include "../framework/components/gameobject_components/sprite_animation_controller.h"
#include "../framework/components/gameobject_components/rect_collider.h"

#include "../framework/graphics/shader.h"
#include "../framework/graphics/texture.h"
#include "../framework/components/gameobject_components/camera.h"
#include "../framework/system/core/input.h"

namespace ns_fretBuzz
{
	class three_d_manager : public ns_system::GameObject
	{
	private:
		

	public:

		ns_system::Camera* m_pPerspectiveCamera = nullptr;

		three_d_manager(GameObject& a_ParentGameObject, std::string a_strName)
			: GameObject(a_ParentGameObject, a_strName, { 0.0f, 0.0f, 5.0f }, { 0.0f, M_PI, 0.0f }, {1.0f, 1.0f, 1.0f})
		{
			ns_system::PerspectiveViewport l_PerspectiveViewport(60.0f, 0.01, 1000.0f );
			m_pPerspectiveCamera = ns_system::Camera::addToGameObject(*this, ns_system::Viewport::PROJECTION_TYPE::PERSPECTIVE, static_cast<ns_system::Viewport*>(&l_PerspectiveViewport));

		}

		/*virtual void update(float a_fDeltaTime) override;
		virtual void render(const ns_system::Camera& a_Camera) override;*/
	};
}