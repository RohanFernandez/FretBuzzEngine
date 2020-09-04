#pragma once
#include "system/game_object_2d.h"
#include "components/gameobject_components/rect_collider.h"

namespace ns_HMGame
{
	class PrefabWall : public FRETBUZZ::GameObject2D
	{
	public:
		PrefabWall(FRETBUZZ::GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH);
	};
}