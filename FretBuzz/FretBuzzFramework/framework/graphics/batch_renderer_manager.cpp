#pragma once
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
			if (s_pInstance != nullptr)
			{
				return;
			}
			s_pInstance = this;
			intialize();
		}

		BatchRendererManager::~BatchRendererManager()
		{
			for (std::vector<ns_graphics::IBatchRenderer*>::iterator l_Iterator = m_vectBatchRenderers.begin();
			l_Iterator != m_vectBatchRenderers.end();)
			{
				delete (*l_Iterator);
				l_Iterator = m_vectBatchRenderers.erase(l_Iterator);
			}
			m_vectBatchRenderers.clear();

			if (s_pInstance == this)
			{
				s_pInstance = nullptr;;
			}
		}

		void BatchRendererManager::intialize()
		{
			m_vectBatchRenderers.emplace_back(new ns_graphics::SpriteBatchRenderer(10));
			m_vectBatchRenderers.emplace_back(new ns_graphics::LineBatchRenderer(100, 10.0f));
		}

		void BatchRendererManager::beginBatches()
		{
			int l_iBatchRendererCount = m_vectBatchRenderers.size();
			for (int l_iBatchRendererIndex = 0; l_iBatchRendererIndex < l_iBatchRendererCount; l_iBatchRendererIndex++)
			{
				m_vectBatchRenderers[l_iBatchRendererIndex]->begin();
			}
		}

		void BatchRendererManager::endBatches()
		{
			int l_iBatchRendererCount = m_vectBatchRenderers.size();
			for (int l_iBatchRendererIndex = 0; l_iBatchRendererIndex < l_iBatchRendererCount; l_iBatchRendererIndex++)
			{
				m_vectBatchRenderers[l_iBatchRendererIndex]->end();
			}
		}

		void BatchRendererManager::flushBatches()
		{
			int l_iBatchRendererCount = m_vectBatchRenderers.size();
			for (int l_iBatchRendererIndex = 0; l_iBatchRendererIndex < l_iBatchRendererCount; l_iBatchRendererIndex++)
			{
				m_vectBatchRenderers[l_iBatchRendererIndex]->flush();
			}
		}

		void BatchRendererManager::endAndflushBatches()
		{
			int l_iBatchRendererCount = m_vectBatchRenderers.size();
			for (int l_iBatchRendererIndex = 0; l_iBatchRendererIndex < l_iBatchRendererCount; l_iBatchRendererIndex++)
			{
				m_vectBatchRenderers[l_iBatchRendererIndex]->end();
				m_vectBatchRenderers[l_iBatchRendererIndex]->flush();
			}
		}
	}
}