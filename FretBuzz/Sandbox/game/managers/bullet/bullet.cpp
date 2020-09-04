#include <fretbuzz_pch.h>
#include "bullet.h"
#include <resource_manager.h>
#include "game/managers/weapon/weapon_manager.h"

namespace ns_HMGame
{

	Bullet::Bullet(FRETBUZZ::GameObject2D* a_GameObject)
		: FRETBUZZ::Behaviour(a_GameObject)
	{
		m_pSpriteRenderer = m_GameObject.getComponent<FRETBUZZ::SpriteRenderer>(FRETBUZZ::COMPONENT_TYPE::SPRITE_RENDERER);
		m_pCollider2D = m_GameObject.getComponent<FRETBUZZ::Collider2D>(FRETBUZZ::COMPONENT_TYPE::COLLIDER_2D);
	}

	void Bullet::setBulletType(std::string a_strBulletSpriteName)
	{
		m_pSpriteRenderer->setSprite(a_strBulletSpriteName);
	}

	void Bullet::shootAt(glm::vec2 a_v2Direction)
	{
		m_fLifetime = 0.0f;
		m_v2Direction = a_v2Direction;
		m_pCollider2D->setLinearVelocity(m_v2Direction * 1000.0f);
	}

	void Bullet::onTriggerEnter2D(FRETBUZZ::Collider2D* a_pIComponent)
	{
		WeaponManager::ReturnBulletToPool(dynamic_cast<PrefabBullet*>(&m_GameObject));
	}

	void Bullet::onTriggerExit2D(FRETBUZZ::Collider2D* a_pIComponent)
	{
		
	}

	void Bullet::onCollisionEnter2D(FRETBUZZ::Collider2D* a_pIComponent)
	{
		WeaponManager::ReturnBulletToPool(dynamic_cast<PrefabBullet*>(&m_GameObject));
	}

	void Bullet::onCollisionExit2D(FRETBUZZ::Collider2D* a_pIComponent)
	{
	
	}

	void Bullet::update(const float& a_fDeltaTime)
	{
		m_fLifetime += a_fDeltaTime;
		if (m_fLifetime > MAX_LIFETIME)
		{
			WeaponManager::ReturnBulletToPool(dynamic_cast<PrefabBullet*>(&m_GameObject));
		}
	}
}