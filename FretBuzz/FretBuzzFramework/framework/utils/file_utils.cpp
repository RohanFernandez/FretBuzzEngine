#pragma once
#include "file_utils.h"
#include <iostream>
#include <fstream>

namespace ns_fretBuzz
{
	namespace ns_utils
	{
		std::string FileUtils::readFile(const std::string a_strFilePath)
		{
			std::ifstream l_File(a_strFilePath);
			if (!l_File)
			{
				std::cout << "file_utils::readFile:: Failed to open file at path :" << a_strFilePath << "\n";
				return nullptr;
			}

			l_File.seekg(0, std::ios::end);
			int l_iStreamCount = l_File.tellg();
			l_File.seekg(0, std::ios::beg);

			char* l_pFileStream = new char[l_iStreamCount];

			memset(l_pFileStream, 0, l_iStreamCount);
			l_File.read(l_pFileStream, l_iStreamCount);

			std::string l_strReturn(l_pFileStream);
			delete[] l_pFileStream;
			l_pFileStream = nullptr;

			l_File.close();

			return l_strReturn;
		}
	}
}