#pragma once
#include "system/game_object_2d.h"

namespace ns_HMGame
{
	class PrefabBullet : public ns_fretBuzz::GameObject2D
	{
	public:
		PrefabBullet(ns_fretBuzz::GameObject* a_ParentGameObject);
		PrefabBullet(ns_fretBuzz::GameObject* a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH);

	};
}