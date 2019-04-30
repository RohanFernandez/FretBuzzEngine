#pragma once
#include <components/collider_2d.h>
#include <graphics/line_batch_renderer.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class GameObject2D;
		class FRETBUZZ_API RectCollider : public Collider2D
			#ifdef _IS_DEBUG_RENDERING
				,public ns_graphics::IRenderer
			#endif
		{
		private:
			RectCollider(GameObject2D& a_GameObject, ColliderData& a_RectColliderData);

			ns_graphics::LineData m_arrRectLineBorders[4];

		protected:
			virtual ~RectCollider();

		public:
			static RectCollider* addToGameObject(GameObject2D& a_GameObject, ColliderData& a_RectColliderData);

			virtual void update(float a_fDeltaTime) override;
			virtual void debugRender(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera) override;
		};
	}
}