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
			glm::quat m_quatRotation;
			glm::vec3 m_v3Scale;

			glm::vec3 m_v3Forward;
			glm::vec3 m_v3Up;
			glm::vec3 m_v3Right;

		public:
			Transform();
			Transform(glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale);
			virtual ~Transform();

			void setLocalRotation(glm::vec3 a_v3Angle);
			void setLocalScale(glm::vec3 a_v3Scale);
			void setLocalPosition(glm::vec3 a_v3Position);

			inline const glm::vec3& getLocalPosition() const
			{
				return m_v3Position;
			}

			inline const glm::quat& getLocalRotation() const
			{
				return m_quatRotation;
			}

			inline const glm::vec3& getLocalScale() const
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