#include <fretbuzz_pch.h>
#include "bullet.h"
#include <system/core/resource_manager.h>

namespace ns_HMGame
{

	Bullet::Bullet(ns_fretBuzz::ns_system::GameObject2D* a_GameObject)
		: ns_fretBuzz::ns_system::Behaviour(a_GameObject)
	{
		m_pSpriteRenderer = m_GameObject.getComponent<ns_fretBuzz::ns_graphics::SpriteRenderer>(ns_fretBuzz::ns_system::COMPONENT_TYPE::SPRITE_RENDERER);
	}

	void Bullet::setBulletType(std::string a_strBulletSpriteName)
	{
		m_pSpriteRenderer->setSprite(a_strBulletSpriteName);
	}

	void Bullet::onTriggerEnter2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent)
	{

	}

	void Bullet::onTriggerExit2D(ns_fretBuzz::ns_system::Collider2D* a_pIComponent)
	{
		
	}
}