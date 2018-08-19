#pragma once
#include "../../resources/libs/pugixml.hpp"
#include "resource_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class AssetLoader
		{
		private:
			static void loadAudioClips(ResourceManager* a_pResourceManager, pugi::xml_node_iterator a_AudioNodeIterator);
			static void loadShaders(ResourceManager* a_pResourceManager, pugi::xml_node_iterator a_AudioNodeIterator);

		public:
			static constexpr char ASSET_RESOURCE_FILE_PATH[] = "resources//assets.xml";
			static constexpr char ATTRIBUTE_ASSET_ID[] = "id";
			static constexpr char ATTRIBUTE_AUDIO_NAME[] = "file_name";

			static constexpr char SHADER_FILE_PATH[] = "resources//shaders//";
			static constexpr char SHADER_NODE_NAME[] = "Shaders";

			static constexpr char TEXTURE_FILE_PATH[] = "resources//textures//";
			static constexpr char TEXTURE_NODE_NAME[] = "Textures";

			static constexpr char AUDIO_CLIP_FILE_PATH[] = "resources//audio//";
			static constexpr char AUDIO_NODE_NAME[] = "Audio";

			static void loadAssets(ResourceManager* a_pResourceManager);

		};
	}
}