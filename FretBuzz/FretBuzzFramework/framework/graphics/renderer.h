#pragma once

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class IRenderer
		{
		public:
			IRenderer() {};
			virtual ~IRenderer() = 0 {};
			virtual void draw() const = 0;
		};
	}
}