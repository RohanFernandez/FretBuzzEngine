#pragma once
#include "system/scene_manager.h"
#include "graphics/shader.h"
#include "graphics/texture.h"

#include "test/CharacterTest.h"
#include "test/EnemyTest.h"

#include "system/core/resource_manager.h"
#include "system/core/window.h"
#include "components/gameobject_components/camera.h"

#include "components//gameobject_components/image.h"
#include "system/core/window.h"

namespace ns_fretBuzz
{
	class FRETBUZZ_API InitState :
		public ns_system::IScene
	{
	public:
		InitState(std::string a_strSceneName) :
			IScene(a_strSceneName)
		{

			ns_system::GameObject2D* l_pLabelGameObj1 = ns_system::GameObject2D::instantiate(m_refRootGameObject, "LABEL1", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
			ns_graphics::Image::addToGameObject(*l_pLabelGameObj1, nullptr, { 1.0f, 0.0f, 0.0f,1.0f }, true);
			//ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj1, { 0.0f, 1.0f, 0.0f,1.0f }, { 150.0f, 100.0f });
			ns_system::RectCollider::addToGameObject(*l_pLabelGameObj1);

			ns_system::GameObject2D* l_pLabelGameObj2 = ns_system::GameObject2D::instantiate(*l_pLabelGameObj1, "LABEL2", { 50.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
			ns_graphics::Image::addToGameObject(*l_pLabelGameObj2, nullptr, { 0.0f, 1.0f, 0.0f,1.0f }, true);
			//ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj2, { 1.0f, 1.0f, 0.0f,1.0f }, { 150.0f, 100.0f });
			ns_system::RectCollider::addToGameObject(*l_pLabelGameObj2);

			ns_system::GameObject2D* l_pLabelGameObj3 = ns_system::GameObject2D::instantiate(*l_pLabelGameObj2, "LABEL3", { 50.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
			ns_graphics::Image::addToGameObject(*l_pLabelGameObj3, nullptr, { 0.0f, 0.0f, 1.0f,1.0f }, true);
			//ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj3, { 0.8f, 0.3f, 0.5f,1.0f }, { 150.0f, 100.0f });
			ns_system::RectCollider::addToGameObject(*l_pLabelGameObj3);

			ns_system::GameObject2D* l_pLabelGameObj4 = ns_system::GameObject2D::instantiate(*l_pLabelGameObj3, "LABEL4", { 50.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
			ns_graphics::Image::addToGameObject(*l_pLabelGameObj4, nullptr, { 1.0f, 1.0f, 0.0f,1.0f }, true);
			//ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj4, { 0.0f, 1.0f, 1.0f,1.0f }, { 150.0f, 100.0f });
			ns_system::RectCollider::addToGameObject(*l_pLabelGameObj4);

			ns_system::GameObject2D* l_pLabelGameObj5 = ns_system::GameObject2D::instantiate(*l_pLabelGameObj4, "LABEL5", { 50.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
			ns_graphics::Image::addToGameObject(*l_pLabelGameObj5, nullptr, { 0.0f, 1.0f, 1.0f,1.0f }, true);
			//ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj5, { 1.0f, 0.0f, 1.0f,1.0f }, { 150.0f, 100.0f });
			ns_system::RectCollider::addToGameObject(*l_pLabelGameObj5);

			//ns_system::GameObject* l_pLabelGameObj6 = ns_system::GameObject::instantiate(*l_pLabelGameObj5, "LABEL6", { 150.0f, 50.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, true);
			//ns_graphics::SpriteRenderer::addToGameObject(*l_pLabelGameObj6, { 1.0f, 1.0f, 1.0f,1.0f }, { 150.0f, 100.0f });
			//ns_system::RectCollider::addToGameObject(*l_pLabelGameObj6, { 150.0f, 100.0f });

			ns_system::GameObject2D* MainParent = ns_system::GameObject2D::instantiate(m_refRootGameObject, "Main_Parent", { 0.0f, 0.0f , 0.0f }, { 0.0f, 0.0f , 0.0f }, { 1.0f, 1.0f, 1.0f }, { 150.0f, 100.0f });
			CharacterTest* l_gameObjChar = new CharacterTest(*MainParent, "character_test", MainParent, m_refRootGameObject);
			
			ns_system::GameObject* m_pCam = ns_system::GameObject::instantiate(*MainParent, "Main_Cam", { 0.0f, 0.0f , 0.0f }, { 0.0f, M_PI , 0.0f }, { 1.0f, 1.0f, 1.0f }, true);
			ns_graphics::OrthographicViewport l_MainCam(-0.5f, 0.5f, -0.5f, 0.5f, -1.0f, 1.0f);
			ns_graphics::Camera::addToGameObject(*m_pCam, ns_graphics::Viewport::PROJECTION_TYPE::ORTHOGRAPHIC, &l_MainCam);

			EnemyTest* l_pEnemy = new EnemyTest(m_refRootGameObject, "enemy_test");
		}
	};
}