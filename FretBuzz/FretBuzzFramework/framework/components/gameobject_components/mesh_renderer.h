#pragma once

#include "../../system/component.h"
#include "../../graphics/shader.h"
#include "../../graphics/mesh.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class GameObject;
		class MeshRenderer : public ns_system::IComponent
		{
		private:
			MeshRenderer(ns_system::GameObject& a_GameObject);
			Mesh* m_pMesh = nullptr;
			Shader* m_pShader = nullptr;

		protected:
			virtual ~MeshRenderer();

		public:
			static MeshRenderer* addToGameObject(ns_system::GameObject& a_GameObject);

			void setMesh(Mesh* a_pMesh);
			Mesh* getMesh();

			void setShader(Shader* a_pShader);
			Shader* getShader();

			virtual void render(const glm::mat4& a_mat4Transformation, const ns_graphics::Camera& a_Camera) override;
		};
	}
}