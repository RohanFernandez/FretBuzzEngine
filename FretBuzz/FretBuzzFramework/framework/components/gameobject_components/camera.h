#pragma once
#include "../../system/component.h"
#include "../../components/viewport.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class GameObject;
		class Camera : public IComponent
		{
		private:
			Camera(GameObject& a_GameObj, Viewport::PROJECTION_TYPE a_ProjectionType, Viewport* a_Viewport);
			Viewport* m_pViewPort = nullptr;
			Viewport::PROJECTION_TYPE m_PROJECTION_TYPE = Viewport::PROJECTION_TYPE::ORTHOGRAPHIC;

			glm::mat4 m_mat4View = glm::mat4(1.0f);

		protected:
			virtual ~Camera();

		public:
			static Camera* addToGameObject(GameObject& a_GameObj, Viewport::PROJECTION_TYPE a_ProjectionType, Viewport* a_pViewport);

			Viewport& getViewport();
			Viewport::PROJECTION_TYPE getProjectionType() const;

			const glm::mat4 updateViewMatrix();
			const glm::mat4 getViewMatrix() const;
			const glm::mat4 getProjectionMatrix() const;
		};
	}
}