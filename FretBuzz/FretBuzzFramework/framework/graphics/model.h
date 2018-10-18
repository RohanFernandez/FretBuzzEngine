#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>
#include "mesh.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		struct Node
		{
		public:
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

		class Model : public ns_system::IManagedResource
		{
		private:
			
			Node* m_pParentNode = nullptr;

			void loadModel(std::string a_strPath);
			void processNode(aiNode* a_pNode, Node* a_pParentNode, const aiScene* a_pScene);
			Mesh* processMesh(aiMesh& a_pMesh, const aiScene* a_pScene);

			void loadTextureOfType(std::vector<Mesh::MeshTexture>& a_vectTextures, aiTextureType a_TextureType, aiMaterial& a_Material);

			std::string m_strDirectory;

		public:

			Model(std::string a_strModelPath);
			virtual ~Model();

		protected:
			virtual void destroyResource() override;
		};
	}
}