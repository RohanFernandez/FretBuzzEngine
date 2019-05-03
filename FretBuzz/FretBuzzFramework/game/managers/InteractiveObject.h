#pragma once
#include <components/gameobject_components/behaviour.h>
#include <components/gameobject_components/image.h>
#include <components/gameobject_components/rect_collider.h>

namespace ns_HMGame
{
	class InteractiveObject : public ns_fretBuzz::ns_system::Behaviour
	{
	private:
		ns_fretBuzz::ns_graphics::Image* m_pImage = nullptr;
		ns_fretBuzz::ns_system::RectCollider* m_pRectCollider = nullptr;

		std::vector<glm::vec4> m_vectColor;
		int m_iColorIndex = 0;

	public:
		InteractiveObject(ns_fretBuzz::ns_system::GameObject& a_GameObject);

		void onLabelHit();
		virtual void onTriggerEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pICollider2D) override;
		virtual void onTriggerExit2D(ns_fretBuzz::ns_system::Collider2D* a_pICollider2D) override;
		virtual void onCollisionEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pICollider2D) override;
		virtual void onCollisionExit2D(ns_fretBuzz::ns_system::Collider2D* a_pICollider2D) override;
	};
}