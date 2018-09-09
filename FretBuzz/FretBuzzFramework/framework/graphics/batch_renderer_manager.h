#pragma once
#include "renderer.h"
#include <vector>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class IBatchRenderer : public IRenderer
		{
		protected:
			IBatchRenderer() : IRenderer() {}

		public:
			virtual ~IBatchRenderer() = 0 {}

			virtual void begin() = 0;
			virtual void end() = 0;
			virtual void flush() = 0;
		};

		class BatchRendererManager
		{
		protected:
			static BatchRendererManager* s_pInstance;

			std::vector<IBatchRenderer*> m_vectBatchRenderers;
			void intialize();

		public:
			BatchRendererManager();
			virtual ~BatchRendererManager();

			void beginBatches();
			void endBatches();
			void flushBatches();
			void endAndflushBatches();
		};
	}
}