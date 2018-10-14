#pragma once
#include "asset_loader.h"
#include "../../graphics/shader.h"
#include "../../graphics/texture.h"
#include "../../components/sprite.h"
#include "../../components/audio_clip.h"
#include "../../components/sprite_animator.h"

#include <fstream>
#include <sstream>

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
				//Load Animations
				else if (l_currentAssetTypeName.compare(SPRITE_ANIMATION_NODE_NAME) == 0)
				{
					loadSpriteAnimations(a_pResourceManager, l_currentAsset);
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
				std::string l_strShaderName;

				for (pugi::xml_attribute_iterator l_CurrentAttribute = l_currentShader->attributes_begin();
					l_CurrentAttribute != l_currentShader->attributes_end();
					l_CurrentAttribute++)
				{
					std::string l_strAttributeName = l_CurrentAttribute->name();
					if (l_strAttributeName.compare(ATTRIBUTE_SHADER_NAME) == 0)
					{
						l_strShaderName = l_CurrentAttribute->value();
					}
					else
					{
						std::cout << "AssetLoader::loadAudioClips:: Could not parse attribute '" << l_strAttributeName << "'";
					}
				}
				ns_graphics::Shader l_Shader(SHADER_FILE_PATH + l_strShaderName);
				if (l_Shader.getIsErrorWhileLoading())
				{
					std::cout << "AssetLoader::loadShader:: Failed to load Shader with id '"<< l_strShaderName << "\n";
					return;
				}

				a_pResourceManager->addResource<ns_graphics::Shader>(l_strShaderName,l_Shader);
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
						float l_fX = 0.0f;
						float l_fY = 0.0f;
						float l_fW = 0.0f;
						float l_fH = 0.0f;
						float l_fOX = 0.0f;
						float l_fOY = 0.0f;
						float l_fPX = 0.0f;
						float l_fPY = 0.0f;
						float l_fOW = 0.0f;
						float l_fOH = 0.0f;

						std::string l_strID;

						for (pugi::xml_attribute_iterator l_CurrSpriteDataAttrib = l_currentSpriteData->attributes_begin();
							l_CurrSpriteDataAttrib != l_currentSpriteData->attributes_end();
							l_CurrSpriteDataAttrib++)
						{
							std::string l_strCurrentAttrib = l_CurrSpriteDataAttrib->name();
							if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_X) == 0)
							{
								l_fX = l_CurrSpriteDataAttrib->as_float();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_Y) == 0)
							{
								l_fY = l_CurrSpriteDataAttrib->as_float();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_W) == 0)
							{
								l_fW = l_CurrSpriteDataAttrib->as_float();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_H) == 0)
							{
								l_fH = l_CurrSpriteDataAttrib->as_float();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_ASSET_ID) == 0)
							{
								l_strID = l_CurrSpriteDataAttrib->as_string();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_OX) == 0)
							{
								l_fOX = l_CurrSpriteDataAttrib->as_float();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_OY) == 0)
							{
								l_fOY = l_CurrSpriteDataAttrib->as_float();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_PX) == 0)
							{
								l_fPX = l_CurrSpriteDataAttrib->as_float();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_PY) == 0)
							{
								l_fPY = l_CurrSpriteDataAttrib->as_float();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_OW) == 0)
							{
								l_fOW = l_CurrSpriteDataAttrib->as_float();
							}
							else if (l_strCurrentAttrib.compare(ATTRIBUTE_SPRITE_OH) == 0)
							{
								l_fOH = l_CurrSpriteDataAttrib->as_float();
							}
							else
							{
								std::cout << "AssetLoader::loadSprites:: Could not parse attribute with name '" << l_strCurrentAttrib << "\n";
							}
						}
						//std::cout << "l_strX:: " << l_strX << "  ,l_strY:: " << l_strY << "  ,l_strW:: " << l_strW << "  ,l_strH:: " << l_strH << "\n";

						//Finding the difference between the original sprite's center and the set pivot of the sprite.
						float l_fSpriteOffsetX = ((l_fW / 2.0f) - ((l_fOW * l_fPX) - l_fOX));
						float l_fSpriteOffsetY = -((l_fH / 2.0f) - ((l_fOH * l_fPY) - l_fOY));

						ns_graphics::Sprite l_Sprite(l_strID, { l_fX, l_fY }, { l_fW, l_fH }, { l_fTextureW,l_fTextureH }, { l_fSpriteOffsetX , l_fSpriteOffsetY }, l_pTexture);
						l_vectSpriteData.emplace_back(l_Sprite);
					}
					ns_graphics::SpriteGroup l_SpriteSheet(l_pTexture, l_vectSpriteData);
					a_pResourceManager->addResource<ns_graphics::SpriteGroup>(l_strSpriteID, l_SpriteSheet);
				}
			}
		}

		void AssetLoader::loadSpriteAnimations(ResourceManager* a_pResourceManager, pugi::xml_node_iterator a_AnimatorNodeIterator)
		{
			for (pugi::xml_node_iterator l_currentAnimator = a_AnimatorNodeIterator->begin();
				l_currentAnimator != a_AnimatorNodeIterator->end();
				l_currentAnimator++)
			{
				std::vector<AnimationState> l_CurrentVectAnimStates;
				std::string l_strAnimatorID = l_currentAnimator->attribute(ATTRIBUTE_ASSET_ID).value();

				if (ResourceManager::getResource<SpriteAnimator>(l_strAnimatorID) != nullptr)
				{
					std::cout << "AssetLoader::loadSpriteAnimations:: Resource with name '" << l_strAnimatorID << "' already exists as a resource \n";
					continue;
				}

				for (pugi::xml_node_iterator l_currentAnimState = l_currentAnimator->begin();
					l_currentAnimState != l_currentAnimator->end();
					l_currentAnimState++)
				{
					std::string l_strAnimId;
					std::string l_strSpriteSheetId;
					float l_fTimePerSprite = 0.0f;
					bool is_loop = false;
					std::string l_strOnCompleteTrigger;
					std::map<std::string, std::string> l_mapTrigger;

					for (pugi::xml_attribute_iterator l_CurrentAttribute = l_currentAnimState->attributes_begin();
						l_CurrentAttribute != l_currentAnimState->attributes_end();
						l_CurrentAttribute++)
					{
						std::string l_strCurrentAttribute = l_CurrentAttribute->name();
						if (l_strCurrentAttribute.compare(ATTRIBUTE_ASSET_ID) == 0)
						{
							l_strAnimId = l_CurrentAttribute->value();
						}
						else if (l_strCurrentAttribute.compare(ATTRIBUTE_SPRITESHEET_ID) == 0)
						{
							l_strSpriteSheetId = l_CurrentAttribute->value();
						}
						else if (l_strCurrentAttribute.compare(ATTRIBUTE_TIME_PER_SPRITE) == 0)
						{
							l_fTimePerSprite = l_CurrentAttribute->as_float();
						}
						else if (l_strCurrentAttribute.compare(ATTRIBUTE_IS_LOOP) == 0)
						{
							is_loop = l_CurrentAttribute->as_bool();
						}
						else if (l_strCurrentAttribute.compare(ATTRIBUTE_ANIM_TRIGGER) == 0)
						{
							std::stringstream l_strStream(l_CurrentAttribute->value());
							std::string l_strCurrentTrigger;
							while (getline(l_strStream, l_strCurrentTrigger, ';'))
							{
								std::string l_strTrigger;
								std::string l_strAnimStateId;
								std::string l_strCurrentExtract;
								std::stringstream l_strStream(l_strCurrentTrigger);

								int l_iExtractIndex = 0;
								while (getline(l_strStream, l_strCurrentExtract, '|'))
								{
									if (l_iExtractIndex == 0)
									{
										l_strTrigger = l_strCurrentExtract;
									}
									else if (l_iExtractIndex == 1)
									{
										l_strAnimStateId = l_strCurrentExtract;
									}
									l_iExtractIndex++;
								}
								l_mapTrigger.insert(std::pair<std::string, std::string>(l_strTrigger, l_strAnimStateId));
							}
						}
						else if (l_strCurrentAttribute.compare(ATTRIBUTE_ON_COMPLETE_TRIGGER) == 0)
						{
							l_strOnCompleteTrigger = l_CurrentAttribute->value();
						}
						else
						{
							std::cout << "AssetLoader::loadAnimations:: Failed to parse anim state attribute with name '" << l_strCurrentAttribute << "'/n";
						}
					}
					l_CurrentVectAnimStates.emplace_back(AnimationState(l_strAnimId, l_strSpriteSheetId, is_loop, l_fTimePerSprite, l_mapTrigger, l_strOnCompleteTrigger));
				}
				SpriteAnimator l_CurrentSpriteAnimController(l_strAnimatorID, l_CurrentVectAnimStates);
				a_pResourceManager->addResource<SpriteAnimator>(l_strAnimatorID, l_CurrentSpriteAnimController);
			}
		}
	}
}