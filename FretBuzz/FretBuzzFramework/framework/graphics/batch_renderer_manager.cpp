#pragma once

#include <iostream>
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
			m_vectBatchRenderers.emplace_back(SpriteBatchRenderer::initialize(10));
			m_vectBatchRenderers.emplace_back(LineBatchRenderer::initialize(100, 10.0f));
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
				std::cout<<"BatchRendererManager::intialize:: BatchRendererManager previously initialized.\n";
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