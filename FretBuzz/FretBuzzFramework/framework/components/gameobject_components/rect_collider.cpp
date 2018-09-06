#pragma once
#include "rect_collider.h"
#include "../../system/game_object.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		RectCollider::RectCollider(GameObject& a_GameObject, glm::vec2 a_v2Dimensions, bool a_bIsStatic, bool a_bIsFixedRotation)
			: IComponent(s_COMPONENT_TYPE, a_GameObject),
			m_bIsStatic{ a_bIsStatic },
			m_bIsFixedRotation{ a_bIsFixedRotation },
			m_v2Dimensions{ a_v2Dimensions }
		{
			b2BodyDef l_bodyDef;
			l_bodyDef.type = m_bIsStatic ? b2_staticBody : b2_dynamicBody;
			glm::vec2 l_Position = m_GameObject.m_Transform.getPosition();
			l_bodyDef.position.Set(l_Position.x, l_Position.y);

			m_pBody = PhysicsEngine::getB2World()->CreateBody(&l_bodyDef);
			
			b2PolygonShape l_boxShape;
			l_boxShape.SetAsBox(m_v2Dimensions.x / 2.0f, m_v2Dimensions.y / 2.0f);

			b2FixtureDef l_fixtureDef;
			l_fixtureDef.shape = &l_boxShape;
			l_fixtureDef.density = 1.0f;
			l_fixtureDef.friction = 0.3f;
			m_pFixture = m_pBody->CreateFixture(&l_fixtureDef);
		}

		RectCollider::~RectCollider()
		{
			PhysicsEngine::getB2World()->DestroyBody(m_pBody);
		}

		RectCollider* RectCollider::addToGameObject(GameObject& a_GameObject, glm::vec2 a_v2Dimensions, bool a_bIsStatic, bool a_bIsFixedRotation)
		{
			return IComponent::isComponentOfTypeExistInGameObj(s_COMPONENT_TYPE, &a_GameObject) ?
				nullptr : new RectCollider(a_GameObject, a_v2Dimensions, a_bIsStatic, a_bIsFixedRotation);
		}

		void RectCollider::update(float a_fDeltaTime)
		{
		
		}
	}
}