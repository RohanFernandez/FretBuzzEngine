#include <fretbuzz_pch.h>
#include "InteractiveObject.h"
#include <system/core/input.h>
#include <system/scene_manager.h>

namespace ns_HMGame
{
	InteractiveObject::InteractiveObject(ns_fretBuzz::ns_system::GameObject& a_GameObject)
		: ns_fretBuzz::ns_system::Behaviour(a_GameObject)
	{
		m_pImage = m_GameObject.getComponent<ns_fretBuzz::ns_graphics::Image>(ns_fretBuzz::ns_system::COMPONENT_TYPE::IMAGE);
		m_vectColor.emplace_back(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
		m_vectColor.emplace_back(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
		m_vectColor.emplace_back(glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f });
	}

	void InteractiveObject::onLabelHit()
	{
		m_pImage->setColor(m_vectColor[(++m_iColorIndex) % m_vectColor.size()]);
	}

	void InteractiveObject::onTriggerEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pICollider2D)
	{
		onLabelHit();
	}

	void InteractiveObject::onTriggerExit2D(ns_fretBuzz::ns_system::Collider2D* a_pICollider2D)
	{
		onLabelHit();
	}

	void InteractiveObject::onCollisionEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pICollider2D)
	{
		onLabelHit();
	}

	void InteractiveObject::onCollisionExit2D(ns_fretBuzz::ns_system::Collider2D* a_pICollider2D)
	{
		onLabelHit();
	}
}