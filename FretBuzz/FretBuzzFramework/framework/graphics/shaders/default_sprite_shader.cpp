#include <fretbuzz_pch.h>
#include "../material.h"
#include "components/gameobject_components/camera.h"
#include "../shader.h"
#include "default_sprite_shader.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		DefaultSpriteShader* DefaultSpriteShader::s_pInstance = nullptr;

		DefaultSpriteShader::DefaultSpriteShader(std::string a_strShaderPath)
			: Shader(a_strShaderPath, SHADER_TYPE::DEFAULT_SPRITE)
		{

		}

		DefaultSpriteShader::~DefaultSpriteShader()
		{

		}

		DefaultSpriteShader* DefaultSpriteShader::initialize(std::string a_strShaderPath)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "DefaultSpriteShader::initialize:: DefaultSpriteShader previously initialized\n";
				return nullptr;
			}

			s_pInstance = new DefaultSpriteShader(a_strShaderPath);
			return s_pInstance;
		}

		void DefaultSpriteShader::bind(const Material& a_Material, const Camera& a_Camera) const
		{
			Shader::bind();
		}

		void DefaultSpriteShader::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}
}