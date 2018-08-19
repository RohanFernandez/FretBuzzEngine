#pragma once
#include "asset_loader.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../components/audio/audio_clip.h"

#include <fstream>
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		void AssetLoader::loadAssets(ResourceManager* a_pResourceManager)
		{
			pugi::xml_document l_doc;
			std::ifstream l_AssetStream(ASSET_RESOURCE_FILE_PATH);
			pugi::xml_parse_result l_ParseResult = l_doc.load(l_AssetStream);

			pugi::xml_node l_AssetMainNode = l_doc.child("Assets");
			pugi::xml_object_range<pugi::xml_node_iterator> l_AssetObject = l_AssetMainNode.children();

			for (pugi::xml_node_iterator l_currentAsset = l_AssetObject.begin();
				l_currentAsset != l_AssetObject.end();
				l_currentAsset++)
			{
				std::string l_currentAssetTypeName = l_currentAsset->name();

				if (l_currentAssetTypeName.compare(SHADER_NODE_NAME) == 0)
				{

				}
				else if (l_currentAssetTypeName.compare(TEXTURE_NODE_NAME) == 0)
				{

				}
				else if (l_currentAssetTypeName.compare(AUDIO_NODE_NAME) == 0)
				{
					loadAudioClips(a_pResourceManager, l_currentAsset);
				}
				else
				{
					std::cout << "Cannot read the asset type ::'"<< l_currentAssetTypeName <<"'\n";
				}
			}

			/////
			ns_graphics::Shader testShader("resources//shaders//vertShader.txt", "resources//shaders//fragShader.txt");
			ns_graphics::Texture testTexture("resources//textures//darksiders.jpg");

			a_pResourceManager->addResource<ns_graphics::Shader>("tShader", testShader);
			a_pResourceManager->addResource<ns_graphics::Texture>("darksider", testTexture);
		}

		void AssetLoader::loadAudioClips(ResourceManager* a_pResourceManager, pugi::xml_node_iterator a_AudioNodeIterator)
		{
			for (pugi::xml_node_iterator l_currentAudio = a_AudioNodeIterator->begin();
				l_currentAudio != a_AudioNodeIterator->end();
				l_currentAudio++)
			{
				std::string l_strAudioID;
				std::string l_strAudioFileName;

				for (pugi::xml_attribute_iterator l_CurrentAttribute = l_currentAudio->attributes_begin();
					l_CurrentAttribute != l_currentAudio->attributes_end();
					l_CurrentAttribute++)
				{
					std::string l_strAttributeName = l_CurrentAttribute->name();
					if (l_strAttributeName.compare(ATTRIBUTE_ASSET_ID) == 0)
					{
						l_strAudioID = l_CurrentAttribute->value();
					}
					else if (l_strAttributeName.compare(ATTRIBUTE_AUDIO_NAME) == 0)
					{
						l_strAudioFileName = l_CurrentAttribute->value();
					}
					else
					{
						std::cout << "AssetLoader::loadAudioClips:: Could not parse attribute '"<< l_strAttributeName <<"'";
					}
				}
				AudioClip l_AudClip = AudioClip(AUDIO_CLIP_FILE_PATH + l_strAudioFileName);
				a_pResourceManager->addResource<AudioClip>(l_strAudioID, l_AudClip);
			}
		}

		void AssetLoader::loadShaders(ResourceManager* a_pResourceManager, pugi::xml_node_iterator a_AudioNodeIterator)
		{

		}
	}
}