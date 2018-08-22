#pragma once
#include "../utils/math.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Transform
		{
		private:
			glm::vec3 m_v3Position;
			glm::vec3 m_v3Rotation;
			glm::vec3 m_v3Scale;

			glm::vec3 m_v3Forward;
			glm::vec3 m_v3Up;
			glm::vec3 m_v3Right;

		public:
			Transform();
			Transform(glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale);
			virtual ~Transform();

			void rotate(glm::vec3 a_v3Angle);
			void scale(glm::vec3 a_v3Scale);
			void translate(glm::vec3 a_v3Translate);

			inline glm::vec3 getPosition() const
			{
				return m_v3Position;
			}

			inline glm::vec3 getRotation() const
			{
				return m_v3Rotation;
			}

			inline glm::vec3 getScale() const
			{
				return m_v3Scale;
			}

			inline glm::vec3 getForward() const
			{
				return m_v3Forward;
			}

			inline glm::vec3 getUp() const
			{
				return m_v3Up;
			}

			inline glm::vec3 getRight() const
			{
				return m_v3Right;
			}

			const glm::mat4 getModelMatrix();
		};
	}
}