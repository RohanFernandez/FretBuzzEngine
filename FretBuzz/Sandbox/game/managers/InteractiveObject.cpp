#include <fretbuzz_pch.h>
#include "InteractiveObject.h"
#include <input.h>
#include <system/scene_manager.h>

namespace ns_HMGame
{
	InteractiveObject::InteractiveObject(ns_fretBuzz::GameObject* a_GameObject)
		: ns_fretBuzz::Behaviour(a_GameObject)
	{
		m_pImage = m_GameObject.getComponent<ns_fretBuzz::Image>(ns_fretBuzz::COMPONENT_TYPE::IMAGE);
		m_vectColor.emplace_back(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
		m_vectColor.emplace_back(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
		m_vectColor.emplace_back(glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f });
	}

	void InteractiveObject::onLabelHit()
	{
		m_pImage->setColor(m_vectColor[(++m_iColorIndex) % m_vectColor.size()]);
	}

	void InteractiveObject::onTriggerEnter2D(ns_fretBuzz::Collider2D* a_pICollider2D)
	{
		onLabelHit();
	}

	void InteractiveObject::onTriggerExit2D(ns_fretBuzz::Collider2D* a_pICollider2D)
	{
		onLabelHit();
	}

	void InteractiveObject::onCollisionEnter2D(ns_fretBuzz::Collider2D* a_pICollider2D)
	{
		onLabelHit();
	}

	void InteractiveObject::onCollisionExit2D(ns_fretBuzz::Collider2D* a_pICollider2D)
	{
		onLabelHit();
	}
}