#pragma once
#include "../system/resource_container.h"
#include "shader.h"
#include <map>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class ShaderManager : ResourceContainer<std::map<Shader::SHADER_TYPE, Shader*>>
		{
		private:
			static ShaderManager* s_pInstance;

			ShaderManager();
			~ShaderManager();

		public:
			static ShaderManager* initialize();
			static const ShaderManager* get();
			void destroy();
		};
	}
}