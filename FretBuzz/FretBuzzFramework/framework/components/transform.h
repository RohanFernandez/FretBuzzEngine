#pragma once
#include <fretbuzz.h>

namespace FRETBUZZ
{
	class  Transform
	{
	friend class GameObject;
	protected:
		glm::vec3 m_v3Position{0.0f};
		glm::quat m_quatRotation;
		glm::vec3 m_v3Scale{1.0f};

		bool m_bIsDirty = false;

		Transform* m_pParentTransform = nullptr;
		glm::mat4 m_mat4ParentTransformation = glm::mat4{1.0f};

		bool getIsDirtyRecusively() const;

	public:
		Transform();
		Transform(glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, Transform* a_pParentTransform);
		virtual ~Transform();

		void setLocalRotation(glm::vec3 a_v3Angle);
		void setLocalRotation(glm::quat a_quatAngle);
		void setLocalScale(glm::vec3 a_v3Scale);
		void setLocalPosition(glm::vec3 a_v3Position);

		void setWorldPosition(glm::vec3 a_v3Position);
		glm::vec3 getWorldPosition() const;

		glm::mat4 getTransformationMatrix();
		glm::mat4 getRotationTransformation();
		glm::mat4 getModelMatrix();

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

		inline glm::vec3 getForward()
		{
			return glm::normalize(getRotationTransformation() * glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f });
		}

		inline glm::vec3 getUp()
		{
			return glm::normalize(getRotationTransformation() * glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f });
		}

		inline glm::vec3 getRight()
		{
			return glm::normalize(getRotationTransformation() * glm::vec4{ 1.0f, 0.0f, 0.0f, 0.0f });
		}
	};
}