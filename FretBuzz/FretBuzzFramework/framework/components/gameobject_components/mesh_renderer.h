#pragma once

#include "system/component.h"
#include "graphics/shader.h"
#include "graphics/renderer.h"
#include "graphics/mesh.h"

namespace ns_fretBuzz
{
	class GameObject;
	class  MeshRenderer : public IComponent, public IRenderer
	{
	private:
		Mesh* m_pMesh = nullptr;
		void setup();

	protected:
		virtual ~MeshRenderer();

	public:
		MeshRenderer(GameObject* a_GameObject, Mesh& a_Mesh);

		Mesh& getMesh();
			
		virtual void render(const glm::mat4& a_mat4Transformation, const Camera& a_Camera) override;
	};
}