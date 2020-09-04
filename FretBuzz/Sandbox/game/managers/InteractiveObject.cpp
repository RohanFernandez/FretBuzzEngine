#include <fretbuzz_pch.h>
#include "InteractiveObject.h"
#include <input.h>
#include <system/scene_manager.h>

namespace ns_HMGame
{
	InteractiveObject::InteractiveObject(FRETBUZZ::GameObject* a_GameObject)
		: FRETBUZZ::Behaviour(a_GameObject)
	{
		m_pImage = m_GameObject.getComponent<FRETBUZZ::Image>(FRETBUZZ::COMPONENT_TYPE::IMAGE);
		m_vectColor.emplace_back(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
		m_vectColor.emplace_back(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
		m_vectColor.emplace_back(glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f });
	}

	void InteractiveObject::onLabelHit()
	{
		m_pImage->setColor(m_vectColor[(++m_iColorIndex) % m_vectColor.size()]);
	}

	void InteractiveObject::onTriggerEnter2D(FRETBUZZ::Collider2D* a_pICollider2D)
	{
		onLabelHit();
	}

	void InteractiveObject::onTriggerExit2D(FRETBUZZ::Collider2D* a_pICollider2D)
	{
		onLabelHit();
	}

	void InteractiveObject::onCollisionEnter2D(FRETBUZZ::Collider2D* a_pICollider2D)
	{
		onLabelHit();
	}

	void InteractiveObject::onCollisionExit2D(FRETBUZZ::Collider2D* a_pICollider2D)
	{
		onLabelHit();
	}
}