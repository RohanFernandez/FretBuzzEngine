#pragma once
#include "asset_loader.h"
#include "../../graphics/shader.h"
#include "../../graphics/texture.h"
#include "../../components/sprite/sprite.h"
#include "../../components/audio/audio_clip.h"


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

				//Load Shaders
				if (l_currentAssetTypeName.compare(SHADER_NODE_NAME) == 0)
				{
					loadShaders(a_pResourceManager, l_currentAsset);
				}
				//Load Textures
				else if (l_currentAssetTypeName.compare(TEXTURE_NODE_NAME) == 0)
				{
					loadTexture(a_pResourceManager, l_currentAsset);
				}
				//Load Audio Clips
				else if (l_currentAssetTypeName.compare(AUDIO_NODE_NAME) == 0)
				{
					loadAudioClips(a_pResourceManager, l_currentAsset);
				}
				//Load Sprites
				else if (l_currentAssetTypeName.compare(SPRITE_NODE_NAME) == 0)
				{
					loadSprites(a_pResourceManager, l_currentAsset);
				}
				else
				{
					std::cout << "Cannot read the asset type ::'"<< l_currentAssetTypeName <<"'\n";
				}
			}
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
				AudioClip l_AudClip(AUDIO_CLIP_FILE_PATH + l_strAudioFileName);
				if (l_AudClip.getIsErrorWhileLoading())
				{
					std::cout << "AssetLoader::loadAudioClips:: Failed to load Shader with id '" << l_strAudioID << "\n";
					return;
				}

				a_pResourceManager->addResource<AudioClip>(l_strAudioID, l_AudClip);
			}
		}

		void AssetLoader::loadShaders(ResourceManager* a_pResourceManager, pugi::xml_node_iterator a_ShaderNodeIterator)
		{
			for (pugi::xml_node_iterator l_currentShader = a_ShaderNodeIterator->begin();
				l_currentShader != a_ShaderNodeIterator->end();
				l_currentShader++)
			{
				std::string l_strShaderID;
				std::string l_strFragShaderName;
				std::string l_strVertShaderName;

				for (pugi::xml_attribute_iterator l_CurrentAttribute = l_currentShader->attributes_begin();
					l_CurrentAttribute != l_currentShader->attributes_end();
					l_CurrentAttribute++)
				{
					std::string l_strAttributeName = l_CurrentAttribute->name();
					if (l_strAttributeName.compare(ATTRIBUTE_ASSET_ID) == 0)
					{
						l_strShaderID = l_CurrentAttribute->value();
					}
					else if (l_strAttributeName.compare(ATTRIBUTE_VERT_NAME) == 0)
					{
						l_strVertShaderName = l_CurrentAttribute->value();
					}
					else if (l_strAttributeName.compare(ATTRIBUTE_FRAG_NAME) == 0)
					{
						l_strFragShaderName = l_CurrentAttribute->value();
					}
					else
					{
						std::cout << "AssetLoader::loadAudioClips:: Could not parse attribute '" << l_strAttributeName << "'";
					}
				}
				ns_graphics::Shader l_Shader(SHADER_FILE_PATH + l_strVertShaderName, SHADER_FILE_PATH + l_strFragShaderName);
				if (l_Shader.getIsErrorWhileLoading())
				{
					std::cout << "AssetLoader::loadShader:: Failed to load Shader with id '"<< l_strShaderID << "\n";
					return;
				}

				a_pResourceManager->addResource<ns_graphics::Shader>(l_strShaderID ,l_Shader);
			}
		}

		void AssetLoader::loadTexture(ResourceManager* a_pResourceManager, pugi::xml_node_iterator a_TextureNodeIterator)
		{
			for (pugi::xml_node_iterator l_currentTexture = a_TextureNodeIterator->begin();
				l_currentTexture != a_TextureNodeIterator->end();
				l_currentTexture++)
			{
				std::string l_strTextureID;
				std::string l_strTextureFileName;

				for (pugi::xml_attribute_iterator l_CurrentAttribute = l_currentTexture->attributes_begin();
					l_CurrentAttribute != l_currentTexture->attributes_end();
					l_CurrentAttribute++)
				{
					std::string l_strAttributeName = l_CurrentAttribute->name();
					if (l_strAttributeName.compare(ATTRIBUTE_ASSET_ID) == 0)
					{
						l_strTextureID = l_CurrentAttribute->value();
					}
					else if (l_strAttributeName.compare(ATRIBUTE_TEXTURE_FILE_NAME) == 0)
					{
						l_strTextureFileName = l_CurrentAttribute->value();
					}
					else
					{
						std::cout << "AssetLoader::loadAudioClips:: Could not parse attribute '" << l_strAttributeName << "'";
					}
				}

				ns_graphics::Texture* l_pTexture = ResourceManager::getResource<ns_graphics::Texture>(l_strTextureID);
				if (l_pTexture == nullptr)
				{
					ns_graphics::Texture l_Texture(TEXTURE_FILE_PATH + l_strTextureFileName);

					if (l_Texture.getIsErrorWhileLoading())
					{
						std::cout << "AssetLoader::loadTexture:: Failed to load AudioClip '" << l_strTextureID << "'\n";
						return;
					}

					a_pResourceManager->addResource<ns_graphics::Texture>(l_strTextureID, l_Texture);
				}
			}
		}

		void AssetLoader::loadSprites(ResourceManager* a_pResourceManager, pugi::xml_node_iterator a_SpriteNodeIterator)
		{
			for (pugi::xml_node_iterator l_currentSpriteSheet = a_SpriteNodeIterator->begin();
				l_currentSpriteSheet != a_SpriteNodeIterator->end();
				l_currentSpriteSheet++)
			{
				std::string l_strTextureId;
				std::string l_strTextureFileName;

				std::string l_strShaderId;
				std::string l_strVertShaderFileName;
				std::string l_strFragShaderFileName;
				std::string l_strTimePerSprite;

				float l_fTextureW = 0.0;
				float l_fTextureH = 0.0f;

				for (pugi::xml_attribute_iterator l_CurrentAttribute = l_currentSpriteSheet->attributes_begin();
					l_CurrentAttribute != l_currentSpriteSheet->attributes_end();
					l_CurrentAttribute++)
				{
					std::string l_strCurrentAttributeName = l_CurrentAttribute->name();
					if (l_strCurrentAttributeName.compare(ATTRIBUTE_TEX_ID) == 0)
					{
						l_strTextureId = l_CurrentAttribute->value();
					}
					else if (l_strCurrentAttributeName.compare(ATRIBUTE_TEXTURE_FILE_NAME) == 0)
					{
						l_strTextureFileName = l_CurrentAttribute->value();
					}
					else if (l_strCurrentAttributeName.compare(ATTRIBUTE_SHADER_ID) == 0)
					{
						l_strShaderId = l_CurrentAttribute->value();
					}
					else if (l_strCurrentAttributeName.compare(ATTRIBUTE_VERT_NAME) == 0)
					{
						l_strVertShaderFileName = l_CurrentAttribute->value();
					}
					else if (l_strCurrentAttributeName.compare(ATTRIBUTE_FRAG_NAME) == 0)
					{
						l_strFragShaderFileName = l_CurrentAttribute->value();
					}
					else if (l_strCurrentAttributeName.compare(ATTRIBUTE_TIME_PER_SPRITE_ID) == 0)
					{
						l_strTimePerSprite = l_CurrentAttribute->value();
					}
					else
					{
						std::cout << "AssetLoader::loadSprites:: Could not parse attribute '" << l_strCurrentAttributeName << "'";
					}
				}
				ns_graphics::Texture* l_pTexture = ResourceManager::getResource<ns_graphics::Texture>(l_strTextureId);
				if (l_pTexture == nullptr)
				{
					ns_graphics::Texture l_Texture(SPRITE_FILE_PATH + l_strTextureFileName);
					a_pResourceManager->addResource<ns_graphics::Texture>(l_strTextureId, l_Texture);
					l_pTexture = a_pResourceManager->getResource<ns_graphics::Texture>(l_strTextureId);
				}
				l_fTextureW = l_pTexture->getWidth();
				l_fTextureH = l_pTexture->getHeight();

				ns_graphics::Shader* l_pShader = ResourceManager::getResource<ns_graphics::Shader>(l_strShaderId);
				if (l_pShader == nullptr)
				{
					ns_graphics::Shader l_Shader(SHADER_FILE_PATH + l_strVertShaderFileName, SHADER_FILE_PATH + l_strFragShaderFileName);
					a_pResourceManager->addResource<ns_graphics::Shader>(l_strShaderId, l_Shader);
					l_pShader = a_pResourceManager->getResource<ns_graphics::Shader>(l_strShaderId);
				}

				for (pugi::xml_node_iterator l_currentSprite = l_currentSpriteSheet->begin();
					l_currentSprite != l_currentSpriteSheet->end();
					l_currentSprite++)
				{
					std::string l_strSpriteID = l_currentSprite->attributes_begin()->value();
					std::vector<ns_graphics::Sprite> l_vectSpriteData;

					for (pugi::xml_node_iterator l_currentSpriteData = l_currentSprite->begin();
						l_currentSpriteData != l_currentSprite->end();
						l_currentSpriteData++)
					{
						std::string l_strX;
						std::string l_strY;
						std::string l_strW;
						std::string l_strH;
						std::string l_strID;

						for (pugi::xml_attribute_iterator l_CurrSpriteDataAttrib = l_currentSpriteData->attributes_begin();
							l_CurrSpriteDataAttrib != l_currentSpriteData->attributes_end();
							l_CurrSpriteDataAttrib++)
						{
							std::string l_strCurrentAttrib = l_CurrSpriteDataAttrib->name();
							if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_X) == 0)
							{
								l_strX = l_CurrSpriteDataAttrib->value();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_Y) == 0)
							{
								l_strY = l_CurrSpriteDataAttrib->value();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_W) == 0)
							{
								l_strW = l_CurrSpriteDataAttrib->value();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_H) == 0)
							{
								l_strH = l_CurrSpriteDataAttrib->value();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_ASSET_ID) == 0)
							{
								l_strID = l_CurrSpriteDataAttrib->value();
							}
							else
							{
								std::cout << "AssetLoader::loadSprites:: Could not parse attribute with name '" << l_strCurrentAttrib << "\n";
							}
						}
						//std::cout << "l_strX:: " << l_strX << "  ,l_strY:: " << l_strY << "  ,l_strW:: " << l_strW << "  ,l_strH:: " << l_strH << "\n";
						ns_graphics::Sprite l_Sprite({ std::stof(l_strX.c_str()), std::stof(l_strY.c_str()) }, { std::stof(l_strW.c_str()), std::stof(l_strH.c_str(),0) }, { l_fTextureW,l_fTextureH }, l_pTexture, l_pShader);
						l_vectSpriteData.emplace_back(l_Sprite);
					}
					ns_graphics::SpriteSheet l_Spite(l_pTexture, l_pShader, l_vectSpriteData, std::stof(l_strTimePerSprite.c_str()));
					a_pResourceManager->addResource<ns_graphics::SpriteSheet>(l_strSpriteID, l_Spite);
				}

			}
		}
	}
}