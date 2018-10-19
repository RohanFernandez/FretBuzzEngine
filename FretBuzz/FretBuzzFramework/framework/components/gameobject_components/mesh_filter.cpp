#pragma once
#include "mesh_filter.h"
#include "../../system/game_object.h"
#include "mesh_renderer.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		MeshFilter::MeshFilter(ns_system::GameObject& a_GameObject, Mesh& a_pMesh)
			: ns_system::IComponent(ns_system::COMPONENT_TYPE::MESH_FILTER, a_GameObject)
		{
			m_pMesh = &a_pMesh;
			if (!IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::MESH_RENDERER, &a_GameObject))
			{
				//MeshRenderer::addToGameObject(a_GameObject, );
			}
			MeshRenderer* l_pMeshRenderer = a_GameObject.getComponent<MeshRenderer>(ns_system::COMPONENT_TYPE::MESH_RENDERER);

			//l_pMeshRenderer->setMesh(m_pMesh);
		}

		MeshFilter::~MeshFilter()
		{
		
		}

		Mesh& MeshFilter::getMesh()
		{
			return *m_pMesh;
		}

		MeshFilter* MeshFilter::addToGameObject(ns_system::GameObject& a_GameObject, Mesh& a_pMesh)
		{
			return IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::MESH_FILTER, &a_GameObject) ?
				nullptr : new MeshFilter(a_GameObject, a_pMesh);
		}
	}
}