#include <fretbuzz_pch.h>
#include "sprite_renderer.h"
#include "../viewport.h"
#include "system/game_object.h"
#include <resource_manager.h>
#include "graphics/sprite_batch_renderer.h"
#include "graphics/shader_manager.h"

namespace ns_fretBuzz
{
	SpriteRenderer::SpriteRenderer(GameObject* a_GameObj, Sprite* a_Sprite)
		: IComponent(COMPONENT_TYPE::SPRITE_RENDERER, a_GameObj),
		IRenderer(),
		m_pSprite{ a_Sprite },
		m_DefaultSprite()
	{
		m_Material.setShader(*ShaderManager::getShaderOfType(Shader::SHADER_TYPE::DEFAULT_SPRITE));
	}

	SpriteRenderer::SpriteRenderer(GameObject* a_GameObj)
		: SpriteRenderer(a_GameObj, nullptr)
	{
		m_Material.setShader(*ShaderManager::getShaderOfType(Shader::SHADER_TYPE::DEFAULT_SPRITE));
	}

	SpriteRenderer::SpriteRenderer(GameObject* a_GameObj, std::string a_strSpriteID)
		: SpriteRenderer(a_GameObj,ResourceManager::getResource<SpriteGroup>(a_strSpriteID)->getSprite(0))
	{
		m_Material.setShader(*ShaderManager::getShaderOfType(Shader::SHADER_TYPE::DEFAULT_SPRITE));
	}

	SpriteRenderer::SpriteRenderer(GameObject* a_GameObj, glm::vec4 a_v4Color, glm::vec2 a_v2Dimensions)
		: IComponent(COMPONENT_TYPE::SPRITE_RENDERER, a_GameObj),
		m_DefaultSprite(a_v2Dimensions, a_v4Color)
	{
		m_Material.setShader(*ShaderManager::getShaderOfType(Shader::SHADER_TYPE::DEFAULT_SPRITE));
	}

	SpriteRenderer::~SpriteRenderer()
	{
		m_pSprite = nullptr;
	}

	void SpriteRenderer::setSprite(Sprite* a_Sprite)
	{
		m_pSprite = a_Sprite;
	}

	void SpriteRenderer::setSprite(std::string a_strSpriteID)
	{
		m_pSprite = ResourceManager::getResource<SpriteGroup>(a_strSpriteID)->getSprite(0);
		setSprite(m_pSprite);
	}

	void SpriteRenderer::render(const glm::mat4& a_mat4Transformation, const Camera& a_Camera)
	{
		Sprite* l_pSpriteToRender = ((m_pSprite == nullptr) ? &m_DefaultSprite : m_pSprite);
		SpriteBatchRenderer::submit(*l_pSpriteToRender, a_mat4Transformation, m_Material);
	}
}