#pragma once
#include "system/component.h"
#include "components/viewport.h"
#include "system/core/layer/layer_mask.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class GameObject;
		class  Camera : public ns_system::IComponent
		{
		private:
			Viewport* m_pViewPort = nullptr;
			Viewport::PROJECTION_TYPE m_PROJECTION_TYPE = Viewport::PROJECTION_TYPE::ORTHOGRAPHIC;

			glm::mat4 m_mat4View = glm::mat4(1.0f);

		protected:
			virtual void editorInspectorRender() override;

			virtual ~Camera();

		public:
			Camera(ns_system::GameObject* a_GameObj, Viewport::PROJECTION_TYPE a_ProjectionType, Viewport* a_Viewport, const ns_system::LayerMask& a_LayerMask, glm::vec4 a_vec4ClearColour = {0.0f, 0.0f,0.0f,1.0f});
			glm::vec4 m_v4ClearColour;
			ns_system::LayerMask m_CullingMask;

			Viewport& getViewport();
			Viewport::PROJECTION_TYPE getProjectionType() const;
			void reset();

			const glm::mat4 updateViewMatrix();
			const glm::mat4 getViewMatrix() const;
			const glm::mat4 getProjectionMatrix() const;

			void zoom(float a_fFOV);
		};
	}
}