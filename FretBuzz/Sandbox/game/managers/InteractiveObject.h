#pragma once
#include <components/gameobject_components/behaviour.h>
#include <components/gameobject_components/image.h>
#include <components/gameobject_components/rect_collider.h>

namespace ns_HMGame
{
	class InteractiveObject : public FRETBUZZ::Behaviour
	{
	private:
		FRETBUZZ::Image* m_pImage = nullptr;
		FRETBUZZ::RectCollider* m_pRectCollider = nullptr;

		std::vector<glm::vec4> m_vectColor;
		int m_iColorIndex = 0;

	public:
		InteractiveObject(FRETBUZZ::GameObject* a_GameObject);

		void onLabelHit();
		virtual void onTriggerEnter2D(FRETBUZZ::Collider2D* a_pICollider2D) override;
		virtual void onTriggerExit2D(FRETBUZZ::Collider2D* a_pICollider2D) override;
		virtual void onCollisionEnter2D(FRETBUZZ::Collider2D* a_pICollider2D) override;
		virtual void onCollisionExit2D(FRETBUZZ::Collider2D* a_pICollider2D) override;
	};
}