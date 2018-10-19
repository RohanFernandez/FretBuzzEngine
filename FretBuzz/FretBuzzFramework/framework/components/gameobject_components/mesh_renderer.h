#pragma once

#include "../../system/component.h"
#include "../../graphics/shader.h"
#include "../../graphics/renderer.h"
#include "../../graphics/mesh.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class GameObject;
		class MeshRenderer : public ns_system::IComponent, public IRenderer
		{
		private:
			MeshRenderer(ns_system::GameObject& a_GameObject, Mesh& a_Mesh);
			Mesh* m_pMesh = nullptr;

		protected:
			virtual ~MeshRenderer();

		public:
			static MeshRenderer* addToGameObject(ns_system::GameObject& a_GameObject, Mesh& a_Mesh);

			Mesh& getMesh();

			virtual void render(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera) override;
		};
	}
}