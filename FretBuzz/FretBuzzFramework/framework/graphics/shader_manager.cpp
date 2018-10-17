#pragma once

#include "shader_manager.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		ShaderManager* ShaderManager::s_pInstance = nullptr;

		ShaderManager::ShaderManager()
			: ResourceContainer<std::map<Shader::SHADER_TYPE, Shader*>>()
		{
		
		}

		ShaderManager::~ShaderManager()
		{
		
		}

		ShaderManager* ShaderManager::initialize()
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "ShaderManager::initialize:: Shader Manager instance has already been previously initialized\n";
				return nullptr;
			}
			s_pInstance = new ShaderManager();
			return s_pInstance;
		}

		const ShaderManager* ShaderManager::get()
		{
			return s_pInstance;
		}

		void ShaderManager::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}
}