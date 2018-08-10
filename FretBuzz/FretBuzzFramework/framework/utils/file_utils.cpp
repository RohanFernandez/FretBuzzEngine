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

		bool FileUtils::readImage(std::string a_strImagePath, BYTE*& a_pImageData, unsigned int& a_iWidth, unsigned int& a_iHeight)
		{
			FREE_IMAGE_FORMAT l_FileImgFormat = FIF_UNKNOWN;
			FIBITMAP *dib = nullptr;
			BYTE* l_pImageBytes = nullptr;

			unsigned int l_iWidth = 0;
			unsigned int l_iHeight = 0;

			const char* l_pImagePath = a_strImagePath.c_str();

			l_FileImgFormat = FreeImage_GetFileType(l_pImagePath, 0);

			if (l_FileImgFormat == FIF_UNKNOWN)
			{
				l_FileImgFormat = FreeImage_GetFIFFromFilename(l_pImagePath);
			}

			if (l_FileImgFormat == FIF_UNKNOWN)
			{
				return false;
			}

			if (FreeImage_FIFSupportsReading(l_FileImgFormat))
			{
				dib = FreeImage_Load(l_FileImgFormat, l_pImagePath);
			}

			if (!dib)
			{
				return false;
			}

			l_pImageBytes = FreeImage_GetBits(dib);

			l_iWidth = FreeImage_GetWidth(dib);
			l_iHeight = FreeImage_GetHeight(dib);

			if ((l_pImageBytes == 0) || (l_iWidth == 0) || (l_iHeight == 0))
			{
				return false;
			}

			a_iWidth = l_iWidth;
			a_iHeight = l_iHeight;

			int l_iPitch = FreeImage_GetPitch(dib);
			int l_iBitsPerPixel = FreeImage_GetBPP(dib);

			int l_BytesPerPixel = (l_iBitsPerPixel / 8);
			int l_iBitsPerRow = a_iWidth * l_BytesPerPixel;

			a_pImageData = new BYTE[l_iBitsPerRow * a_iHeight];

			for (int l_iYIndex = 0; l_iYIndex < a_iHeight; l_iYIndex++)
			{
				memcpy(&a_pImageData[l_iYIndex * l_iBitsPerRow], &l_pImageBytes[l_iYIndex * l_iPitch], l_iBitsPerRow);
			}

			FreeImage_Unload(dib);
			return true;
		}
	}
}