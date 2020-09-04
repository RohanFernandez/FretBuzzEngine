#include <fretbuzz_pch.h>
#include "shader_manager.h"
#include "shader_factory.h"

namespace FRETBUZZ
{
	//singleton instance
	ShaderManager* ShaderManager::s_pInstance = nullptr;

	ShaderManager::ShaderManager()
		: ResourceContainer<std::map<Shader::SHADER_TYPE, Shader*>>()
	{
			
	}

	ShaderManager::~ShaderManager()
	{
		unregisterAll();
	}

	ShaderManager* ShaderManager::initialize()
	{
		if (s_pInstance != nullptr)
		{
			ENGINE_WARN("ShaderManager::initialize:: Shader Manager instance has already been previously initialized");
			return nullptr;
		}
		s_pInstance = new ShaderManager();
		ShaderFactory::initialize();
		return s_pInstance;
	}

	Shader* ShaderManager::getShaderOfType(Shader::SHADER_TYPE a_ShaderType)
	{
		return s_pInstance->getResource(a_ShaderType);
	}

	ShaderManager* ShaderManager::get()
	{
		return s_pInstance;
	}

	void ShaderManager::destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	void ShaderManager::registerShader(Shader::SHADER_TYPE a_ShaderType, Shader* a_pShader)
	{
		registerResource(a_ShaderType, a_pShader);
	}

	void ShaderManager::unregisterShader(Shader::SHADER_TYPE a_ShaderType)
	{
		Shader* l_pUnregisteredShader = unregisterResource(a_ShaderType);
		if (l_pUnregisteredShader != nullptr)
		{
			l_pUnregisteredShader->destroy();
		}
	}

	void ShaderManager::unregisterAll()
	{
		for (auto l_Iterator = m_Container.begin();
			l_Iterator != m_Container.end();)
		{
			l_Iterator->second->destroy();
			l_Iterator = m_Container.erase(l_Iterator);
		}
	}
}