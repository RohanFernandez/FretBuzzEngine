#pragma once
#include "../../system/component.h"
#include "../../graphics/model.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class GameObject;
		class MeshFilter : public ns_system::IComponent
		{
		private:
			MeshFilter(ns_system::GameObject& a_GameObject, Mesh& a_pModel);
			Mesh* m_pMesh = nullptr;

		protected:
			virtual ~MeshFilter();

		public:
			static MeshFilter* addToGameObject(ns_system::GameObject& a_GameObject, Mesh& a_pMesh);
			Mesh& getMesh();
		};
	}
}