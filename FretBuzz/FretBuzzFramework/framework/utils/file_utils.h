#pragma once
#include <string>

namespace ns_fretBuzz
{
	namespace ns_utils
	{
		struct FileUtils
		{
			static std::string readFile(const std::string a_strFilePath);
		};
	}
}