#pragma once
#include <components/gameobject_components/behaviour.h>
#include <components/gameobject_components/sprite_renderer.h>

namespace ns_HMGame
{
	class Bullet : public FRETBUZZ::Behaviour
	{
	private:
		FRETBUZZ::SpriteRenderer* m_pSpriteRenderer = nullptr;
		FRETBUZZ::Collider2D* m_pCollider2D = nullptr;

		float m_fLifetime = 0.0f;
		static constexpr float MAX_LIFETIME = 3.0f;

		glm::vec2 m_v2Direction{1.0f, 1.0f};

	public:
		Bullet(FRETBUZZ::GameObject2D* a_GameObject);
		void setBulletType(std::string a_strBulletSpriteName);

		void shootAt(glm::vec2 a_v2Direction);

		virtual void onTriggerEnter2D(FRETBUZZ::Collider2D* a_pIComponent) override;
		virtual void onTriggerExit2D(FRETBUZZ::Collider2D* a_pIComponent) override;

		virtual void onCollisionEnter2D(FRETBUZZ::Collider2D* a_pIComponent) override;
		virtual void onCollisionExit2D(FRETBUZZ::Collider2D* a_pIComponent) override;

		void virtual update(const float& a_fDeltaTime) override;
	};
}