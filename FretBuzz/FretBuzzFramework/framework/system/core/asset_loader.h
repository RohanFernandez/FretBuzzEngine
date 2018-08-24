#pragma once
#include "../../../resources/libs/pugixml.hpp"
#include "resource_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class AssetLoader
		{
		private:
			static void loadAudioClips(ResourceManager* a_pResourceManager, pugi::xml_node_iterator a_AudioNodeIterator);
			static void loadShaders(ResourceManager* a_pResourceManager, pugi::xml_node_iterator a_ShaderNodeIterator);
			static void loadTexture(ResourceManager* a_pResourceManager, pugi::xml_node_iterator a_TextureNodeIterator);
			static void loadSprites(ResourceManager* a_pResourceManager, pugi::xml_node_iterator a_SpriteNodeIterator);

		public:
			//Asset
			static constexpr char ASSET_RESOURCE_FILE_PATH[] = "resources//assets.xml";
			static constexpr char ATTRIBUTE_ASSET_ID[] = "id";
			static constexpr char ATTRIBUTE_AUDIO_NAME[] = "file_name";

			//Shader
			static constexpr char SHADER_FILE_PATH[] = "resources//shaders//";
			static constexpr char SHADER_NODE_NAME[] = "Shaders";
			static constexpr char ATTRIBUTE_VERT_NAME[] = "vert";
			static constexpr char ATTRIBUTE_FRAG_NAME[] = "frag";

			//Texture
			static constexpr char TEXTURE_FILE_PATH[] = "resources//textures//";
			static constexpr char TEXTURE_NODE_NAME[] = "Textures";
			static constexpr char ATRIBUTE_TEXTURE_FILE_NAME[] = "file_name";

			//Audio
			static constexpr char AUDIO_CLIP_FILE_PATH[] = "resources//audio//";
			static constexpr char AUDIO_NODE_NAME[] = "Audio";

			//Sprites
			static constexpr char SPRITE_FILE_PATH[] = "resources//sprites//";
			static constexpr char SPRITE_NODE_NAME[] = "Sprites";
			static constexpr char ATTRIBUTE_TEX_ID[] = "tex_id";
			static constexpr char ATTRIBUTE_SHADER_ID[] = "shader_id";
			static constexpr char ATTRIBUTE_TIME_PER_SPRITE_ID[] = "time_per_sprite";
			static constexpr char ATTRIBUTE_SPRITE_X[] = "x";
			static constexpr char ATTRIBUTE_SPRITE_Y[] = "y";
			static constexpr char ATTRIBUTE_SPRITE_W[] = "w";
			static constexpr char ATTRIBUTE_SPRITE_H[] = "h";

			static void loadAssets(ResourceManager* a_pResourceManager);

		};
	}
}