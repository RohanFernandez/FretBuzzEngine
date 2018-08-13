#pragma once
#include <FreeImage.h>
#include <string>

namespace ns_fretBuzz
{
	namespace ns_utils
	{
		struct FileUtils
		{
			static std::string readFile(const std::string a_strFilePath);
			static bool readImage(std::string a_strImagePath, BYTE*& a_pImageData, unsigned int& a_iWidth, unsigned int& a_iHeight, int& a_iChannels);
		};
	}
}