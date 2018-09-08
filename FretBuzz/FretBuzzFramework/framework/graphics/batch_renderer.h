#pragma once
#include "renderer.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class BatchRenderer : public IRenderer
		{
		protected:
			BatchRenderer() : IRenderer(){}

		public:
			virtual ~BatchRenderer() = 0 {}

			virtual void begin() = 0;
			virtual void end() = 0;
			virtual void flush() = 0;
		};
	}
}