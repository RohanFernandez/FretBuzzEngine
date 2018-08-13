#pragma once
#include "renderer.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class Renderer2D : public IRenderer
		{
		public:
			Renderer2D();
			~Renderer2D();

			virtual void draw() const override;
		};
	}
}