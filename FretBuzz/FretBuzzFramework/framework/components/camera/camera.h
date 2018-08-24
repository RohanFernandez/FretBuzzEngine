#pragma once
#include "../../system/core/window.h"
#include "../transform.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Camera
		{
		public:
			enum PROJECTION_TYPE
			{
				ORTHOGRAPHIC,
				PERSPECTIVE
			};

			enum CONTROLLER_TYPE
			{
				NONE,
				FPS
			};

		protected:
			PROJECTION_TYPE m_ProjectionType;
			glm::mat4 m_mat4Projection;
			glm::mat4 m_mat4View;

			Camera() = delete;
			Camera(glm::vec3 a_v3Pos, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, PROJECTION_TYPE a_ProjectionType, glm::mat4 a_mat4Projection);

		public:
			virtual ~Camera() = 0 {};

			//Returns projection type i.e orthographic / perspective.
			inline PROJECTION_TYPE getProjectionType() const
			{
				return m_ProjectionType;
			}

			Transform m_transform;
			const glm::mat4& updateViewMatrix();

			inline const glm::mat4 getProjectionMatrix() const
			{
				return m_mat4Projection;
			}

			inline const glm::mat4& getViewMatrix() const
			{
				return m_mat4View;
			}
		};

		class OrthographicCamera : public Camera
		{
		public:
			OrthographicCamera(glm::vec3 a_v3Pos, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, float a_fleft, float a_fRight, float a_fBotton, float a_fTop, float a_fNear, float a_fFar)
				: Camera(a_v3Pos, a_v3Rotation, a_v3Scale, ORTHOGRAPHIC,
					glm::ortho(a_fleft, a_fRight, a_fBotton, a_fTop, a_fNear, a_fFar))
			{
			}

			OrthographicCamera(glm::vec3 a_v3Pos, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, float a_fNear, float a_fFar)
				: OrthographicCamera(a_v3Pos, a_v3Rotation, a_v3Scale, -(float)Window::getWidth() / 2.0f, (float)Window::getWidth() / 2.0f, -(float)Window::getHeight() / 2.0f, (float)Window::getHeight() / 2.0f, a_fNear, a_fFar)
			{	
			}

			virtual ~OrthographicCamera()
			{
			}

			//resets the projection matrix
			void setProjectionMatrix(float a_fLeft, float a_fRight, float a_fBotton, float a_fTop, float a_fNear, float a_fFar)
			{
				m_mat4Projection = glm::ortho(a_fLeft, a_fRight, a_fBotton, a_fTop, a_fNear, a_fFar);
			}
		};

		class PerspectiveCamera : public Camera
		{
		public:
			PerspectiveCamera(glm::vec3 a_v3Pos, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale,float a_fDegreesFOV, float a_fAspectRatio, float a_fNear, float a_fFar)
				: Camera(a_v3Pos, a_v3Rotation, a_v3Scale, PERSPECTIVE,
					glm::perspective(glm::radians(a_fDegreesFOV), a_fAspectRatio, a_fNear, a_fFar))
			{
			}

			PerspectiveCamera(glm::vec3 a_v3Pos, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, float a_fDegreesFOV, float a_fNear, float a_fFar)
				: PerspectiveCamera(a_v3Pos, a_v3Rotation, a_v3Scale, a_fDegreesFOV, (float)Window::getWidth() / (float)Window::getHeight(), a_fNear, a_fFar)
			{
			}

			virtual ~PerspectiveCamera()
			{
			}

			//resets the projection matrix
			void setProjectionMatrix(float a_fDegreesFOV, float a_fAspectRatio, float a_fNear, float a_fFar)
			{
				m_mat4Projection = glm::perspective(glm::radians(a_fDegreesFOV), a_fAspectRatio, a_fNear, a_fFar);
			}
		};
	}
}