#include <fretbuzz_pch.h>
#include "batch_renderer_manager.h"

#include "sprite_batch_renderer.h"
#include "line_batch_renderer.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		BatchRendererManager* BatchRendererManager:: s_pInstance = nullptr;

		BatchRendererManager::BatchRendererManager()
		{
			m_vectBatchRenderers.emplace_back(SpriteBatchRenderer::initialize(100));
			m_vectBatchRenderers.emplace_back(LineBatchRenderer::initialize(100, 3.0f));
		}

		BatchRendererManager::~BatchRendererManager()
		{
			for (std::vector<IBatchRenderer*>::iterator l_Iterator = m_vectBatchRenderers.begin();
			l_Iterator != m_vectBatchRenderers.end();)
			{
				(*l_Iterator)->destroy();
				l_Iterator = m_vectBatchRenderers.erase(l_Iterator);
			}
			m_vectBatchRenderers.clear();
		}

		BatchRendererManager* BatchRendererManager::intialize()
		{
			if (s_pInstance != nullptr)
			{
				ENGINE_WARN("BatchRendererManager::intialize:: BatchRendererManager previously initialized.");
				return nullptr;
			}

			s_pInstance = new BatchRendererManager();
			return s_pInstance;
		}

		void BatchRendererManager::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}

		const BatchRendererManager* BatchRendererManager::get()
		{
			return s_pInstance;
		}

		void BatchRendererManager::beginBatches()
		{
			size_t l_iBatchRendererCount = m_vectBatchRenderers.size();
			for (size_t l_iBatchRendererIndex = 0; l_iBatchRendererIndex < l_iBatchRendererCount; l_iBatchRendererIndex++)
			{
				m_vectBatchRenderers[l_iBatchRendererIndex]->begin();
			}
		}

		void BatchRendererManager::endBatches()
		{
			size_t l_iBatchRendererCount = m_vectBatchRenderers.size();
			for (size_t l_iBatchRendererIndex = 0; l_iBatchRendererIndex < l_iBatchRendererCount; l_iBatchRendererIndex++)
			{
				m_vectBatchRenderers[l_iBatchRendererIndex]->end();
			}
		}

		void BatchRendererManager::flushBatches()
		{
			size_t l_iBatchRendererCount = m_vectBatchRenderers.size();
			for (size_t l_iBatchRendererIndex = 0; l_iBatchRendererIndex < l_iBatchRendererCount; l_iBatchRendererIndex++)
			{
				m_vectBatchRenderers[l_iBatchRendererIndex]->flush();
			}
		}

		void BatchRendererManager::endAndflushBatches()
		{
			size_t l_iBatchRendererCount = m_vectBatchRenderers.size();
			for (size_t l_iBatchRendererIndex = 0; l_iBatchRendererIndex < l_iBatchRendererCount; l_iBatchRendererIndex++)
			{
				m_vectBatchRenderers[l_iBatchRendererIndex]->end();
				m_vectBatchRenderers[l_iBatchRendererIndex]->flush();
			}
		}
	}
}