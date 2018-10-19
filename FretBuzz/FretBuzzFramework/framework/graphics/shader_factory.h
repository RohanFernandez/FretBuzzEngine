#pragma once
#include "shaders/phong_shader.h"
#include "shaders/default_3d_shader.h"
#include "shaders/default_sprite_shader.h"
#include "shaders/default_line_shader.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		struct ShaderFactory
		{
			static constexpr char SHADER_NAME_PHONG[] = "phong";
			static constexpr char SHADER_NAME_DEFAULT_3D[] = "default_3d";
			static constexpr char SHADER_NAME_DEFAULT_SPRITE[] = "default_sprite";
			static constexpr char SHADER_NAME_DEFAULT_LINE[] = "default_line";

			static void initialize()
			{
				DefaultSpriteShader::initialize(SHADER_NAME_DEFAULT_SPRITE);
				PhongShader::initialize(SHADER_NAME_PHONG);
				Default3DShader::initialize(SHADER_NAME_DEFAULT_3D);
				DefaultLineShader::initialize(SHADER_NAME_DEFAULT_LINE);
			}
		};
	}
}