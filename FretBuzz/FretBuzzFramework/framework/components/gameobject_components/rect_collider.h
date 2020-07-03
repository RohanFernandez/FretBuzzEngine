#pragma once
#include <components/collider_2d.h>
#include <graphics/line_batch_renderer.h>

namespace ns_fretBuzz
{
	class GameObject2D;
	class  RectCollider : public Collider2D
		#ifdef _IS_DEBUG_RENDERING
			,public IRenderer
		#endif
	{
	private:

		LineData m_arrRectLineBorders[4];

	protected:
		virtual ~RectCollider();

	public:
		RectCollider(GameObject2D* a_GameObject, ColliderData& a_RectColliderData);
			
		//virtual void update(float a_fDeltaTime) override;
		virtual void lateUpdate(const float& a_fDeltaTime) override;
		virtual void debugRender(const glm::mat4& a_mat4Transformation, const Camera& a_Camera) override;
	};
}