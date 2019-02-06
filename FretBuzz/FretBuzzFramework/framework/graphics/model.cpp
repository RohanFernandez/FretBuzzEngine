#include <fretbuzz_pch.h>
#include "model.h"
#include <iostream>
#include "system/core/resource_manager.h"
#include "texture.h"
#include "components/gameobject_components/mesh_renderer.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Model::Model(std::string a_strModelPath)
			: ns_system::IManagedResource()
		{
			loadModel(a_strModelPath);
		}

		Model::~Model()
		{
			
		}

		void Model::loadModel(std::string a_strPath)
		{
			Assimp::Importer l_Importer;
			const aiScene *l_pScene = l_Importer.ReadFile(a_strPath, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!l_pScene || l_pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !l_pScene->mRootNode)
			{
				std::cout << "Model::loadModel:: Failed to load model ::" << l_Importer.GetErrorString() << "\n";
				return;
			}

			m_strDirectory = a_strPath.substr(0, a_strPath.find_last_of('/'));

			m_pRootNode = new Node();
			processNode(l_pScene->mRootNode, m_pRootNode, l_pScene);
		}

		void Model::processNode(aiNode* a_pNode, Node* a_pLoadedNode, const aiScene* a_pScene)
		{
			a_pLoadedNode->m_strName = a_pNode->mName.C_Str();

			int l_iMeshCount = a_pNode->mNumMeshes;
			for (unsigned int l_iMeshIndex = 0; l_iMeshIndex < l_iMeshCount; l_iMeshIndex++)
			{
				aiMesh* l_pMesh = a_pScene->mMeshes[a_pNode->mMeshes[l_iMeshIndex]];
				a_pLoadedNode->m_pMesh = processMesh(*l_pMesh, a_pScene);
			}

			unsigned int l_iChildCount = a_pNode->mNumChildren;
			for (unsigned int l_iChildIndex = 0; l_iChildIndex < l_iChildCount; l_iChildIndex++)
			{
				Node* l_pCurrentNode = new Node();
				a_pLoadedNode->m_vectChildNodes.emplace_back(l_pCurrentNode);
				processNode(a_pNode->mChildren[l_iChildIndex], l_pCurrentNode, a_pScene);
			}
		}

		Mesh* Model::processMesh(aiMesh& a_Mesh, const aiScene* a_pScene)
		{
			std::vector<Mesh::Vertex> l_vectVertices;
			std::vector<unsigned int> l_vectIndices;
			std::vector<Mesh::MeshTexture> l_vectTextures;

			unsigned int l_iVertexCount = a_Mesh.mNumVertices;
			for (unsigned int l_iVertexIndex = 0; l_iVertexIndex < l_iVertexCount; l_iVertexIndex++)
			{
				Mesh::Vertex l_CurrentVertex;

				aiVector3D l_v3Current = a_Mesh.mVertices[l_iVertexIndex];
				l_CurrentVertex.m_v3Position = { l_v3Current.x, l_v3Current.y, l_v3Current.z };

				l_v3Current = a_Mesh.mNormals[l_iVertexIndex];
				l_CurrentVertex.m_v3Normal = { l_v3Current.x, l_v3Current.y, l_v3Current.z };
				
				l_CurrentVertex.m_v2TexCoords = (a_Mesh.mTextureCoords[0] != nullptr) ?
				glm::vec2{a_Mesh.mTextureCoords[0][l_iVertexIndex].x, a_Mesh.mTextureCoords[0][l_iVertexIndex].y} :
				glm::vec2{0.0f, 0.0f};

				l_vectVertices.emplace_back(l_CurrentVertex);
			}

			unsigned int l_iIndexCount = a_Mesh.mNumFaces;
			for (unsigned int l_iIndex = 0; l_iIndex < l_iIndexCount; l_iIndex++)
			{
				aiFace& l_Face = a_Mesh.mFaces[l_iIndex];
				unsigned int IndexCount = l_Face.mNumIndices;
				for (unsigned int l_iFaceIndex = 0; l_iFaceIndex < IndexCount; l_iFaceIndex++)
				{
					l_vectIndices.emplace_back(l_Face.mIndices[l_iFaceIndex]);
				}
			}

			if (a_Mesh.mMaterialIndex >= 0)
			{
				aiMaterial& l_Material = *a_pScene->mMaterials[a_Mesh.mMaterialIndex];
				loadTextureOfType(l_vectTextures, aiTextureType_DIFFUSE, l_Material);
				loadTextureOfType(l_vectTextures, aiTextureType_SPECULAR, l_Material);
				loadTextureOfType(l_vectTextures, aiTextureType_AMBIENT, l_Material);
				loadTextureOfType(l_vectTextures, aiTextureType_OPACITY, l_Material);
			}

			return new Mesh(l_vectVertices, l_vectIndices, l_vectTextures);
		}

		void Model::loadTextureOfType(std::vector<Mesh::MeshTexture>& a_vectTextures, aiTextureType a_TextureType, aiMaterial& a_Material)
		{
			unsigned int l_iCurrentTexTypeCount = a_Material.GetTextureCount(a_TextureType);
			if (l_iCurrentTexTypeCount > 0)
			{
				aiString l_strTextureName;
				a_Material.GetTexture(a_TextureType, 0, &l_strTextureName);
				
				std::string l_strTexturePath = m_strDirectory + "/" + l_strTextureName.C_Str();
				Texture* l_pTexture = ns_system::ResourceManager::getResource<Texture>(l_strTexturePath);
				if (l_pTexture == nullptr)
				{
					Texture l_texture(l_strTexturePath);
					ns_system::ResourceManager::s_addResource<Texture>(l_strTexturePath, l_texture);
					l_pTexture = ns_system::ResourceManager::getResource<Texture>(l_strTexturePath);
				}

				Mesh::MeshTexture l_MeshTexture;
				l_MeshTexture.m_pTexture = l_pTexture;

				switch (a_TextureType)
				{
				case aiTextureType_DIFFUSE:
					l_MeshTexture.m_Type = Mesh::MeshTexture::DIFFUSE;
					break;

				case aiTextureType_SPECULAR:
					l_MeshTexture.m_Type = Mesh::MeshTexture::SPECULAR;
					break;

				case aiTextureType_AMBIENT:
					l_MeshTexture.m_Type = Mesh::MeshTexture::DIFFUSE;
					break;

				case aiTextureType_OPACITY:
					l_MeshTexture.m_Type = Mesh::MeshTexture::DIFFUSE;
					break;

				default:
					l_MeshTexture.m_Type = Mesh::MeshTexture::DIFFUSE;
					break;
				}

				a_vectTextures.emplace_back(l_MeshTexture);
			}
		}

		void Model::destroyResource()
		{
			if (m_pRootNode != nullptr)
			{
				delete m_pRootNode;
				m_pRootNode = nullptr;
			}
		}

		void Model::addToGameObject(ns_system::GameObject& a_GameObject, Model& a_Model)
		{
			if (a_Model.m_pRootNode != nullptr)
			{
				addMeshToGameObject(a_GameObject, *a_Model.m_pRootNode);
			}
		}

		void Model::addMeshToGameObject(ns_system::GameObject& a_GameObject, Node& a_Node)
		{
			if (a_Node.m_pMesh != nullptr)
			{
				if (MeshRenderer::addToGameObject(a_GameObject, *a_Node.m_pMesh) == nullptr)
				{
					std::cout << "Model::addMeshToGameObject:: Failed to load mesh renderer because a mesh renderer already exists.\n";
				}
			}

			int l_iChildCount = a_Node.m_vectChildNodes.size();
			for (int l_iChildIndex = 0; l_iChildIndex < l_iChildCount; l_iChildIndex++)
			{
				Node& l_CurrentNode = *a_Node.m_vectChildNodes[l_iChildIndex];
				ns_system::GameObject* l_pChildGameObject = ns_system::GameObject::instantiate(a_GameObject, l_CurrentNode.m_strName);
				addMeshToGameObject(*l_pChildGameObject, l_CurrentNode);
			}
		}
	}
}