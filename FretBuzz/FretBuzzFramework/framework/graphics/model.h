#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include "mesh.h"
#include "system/game_object.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		struct Node
		{
		public:
			std::string m_strName;
			Mesh* m_pMesh = nullptr;
			std::vector<Node*> m_vectChildNodes;

			~Node()
			{
				if (m_pMesh != nullptr)
				{
					delete m_pMesh;
					m_pMesh = nullptr;
				}

				for (auto l_Iterator = m_vectChildNodes.begin();
					l_Iterator != m_vectChildNodes.end();)
				{
					delete (*l_Iterator);
					l_Iterator = m_vectChildNodes.erase(l_Iterator);
				}
			}
		};

		class GameObject;
		class Model : public ns_system::IManagedResource
		{
		private:
			
			Node* m_pRootNode = nullptr;

			void loadModel(std::string a_strPath);
			void processNode(aiNode* a_pNode, Node* a_pParentNode, const aiScene* a_pScene);
			Mesh* processMesh(aiMesh& a_pMesh, const aiScene* a_pScene);

			void loadTextureOfType(std::vector<Mesh::MeshTexture>& a_vectTextures, aiTextureType a_TextureType, aiMaterial& a_Material);

			std::string m_strDirectory;

			static void addMeshToGameObject(ns_system::GameObject& a_GameObject, Node& a_Node);

		public:

			Model(std::string a_strModelPath);
			virtual ~Model();

			static void addToGameObject(ns_system::GameObject& a_GameObject, Model& a_Model);

		protected:
			virtual void destroyResource() override;
		};
	}
}