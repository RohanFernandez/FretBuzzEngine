#pragma once
#include "../system/core/window.h"
#include "transform.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Viewport
		{
		public:
			enum class PROJECTION_TYPE
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

			Viewport() = delete;
			Viewport(glm::vec3 a_v3Pos, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, PROJECTION_TYPE a_ProjectionType, glm::mat4 a_mat4Projection);
			glm::vec2 m_v2NearFar = {};


		public:
			virtual ~Viewport() = 0 {};

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

			const glm::vec2& getNearFar() const
			{
				return m_v2NearFar;
			}
		};

		class OrthographicViewport : public Viewport
		{
		protected:
			glm::vec2 m_v2LeftRight;
			glm::vec2 m_v2BottomTop;

		public:
			OrthographicViewport(glm::vec3 a_v3Pos, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, float a_fleft, float a_fRight, float a_fBottom, float a_fTop, float a_fNear, float a_fFar)
				: Viewport(a_v3Pos, a_v3Rotation, a_v3Scale, PROJECTION_TYPE::ORTHOGRAPHIC,
					glm::ortho(a_fleft, a_fRight, a_fBottom, a_fTop, a_fNear, a_fFar))
			{
				m_v2NearFar = { a_fNear, a_fFar };
				m_v2LeftRight = { a_fleft, a_fRight };
				m_v2BottomTop = { a_fBottom , a_fTop };
			}

			OrthographicViewport(glm::vec3 a_v3Pos, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, float a_fNear, float a_fFar)
				: OrthographicViewport(a_v3Pos, a_v3Rotation, a_v3Scale, -(float)Window::getWidth() / 2.0f, (float)Window::getWidth() / 2.0f, -(float)Window::getHeight() / 2.0f, (float)Window::getHeight() / 2.0f, a_fNear, a_fFar)
			{	
			}

			virtual ~OrthographicViewport()
			{
			}

			//resets the projection matrix
			void setProjectionMatrix(float a_fLeft, float a_fRight, float a_fBottom, float a_fTop, float a_fNear, float a_fFar)
			{
				m_mat4Projection = glm::ortho(a_fLeft, a_fRight, a_fBottom, a_fTop, a_fNear, a_fFar);

				m_v2BottomTop = {a_fBottom, a_fTop};
				m_v2LeftRight = { a_fLeft, a_fRight};
				m_v2NearFar = { a_fNear, a_fFar };
			}

			const glm::vec2& getTopBottom() const
			{
				return m_v2BottomTop;
			}

			const glm::vec2& getLeftRight() const
			{
				return m_v2LeftRight;
			}
		};

		class PerspectiveViewport : public Viewport
		{
		protected:
			float m_fFOV = 0.0f;
			float m_fAspectRatio = 0.0f;

		public:
			PerspectiveViewport(glm::vec3 a_v3Pos, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale,float a_fDegreesFOV, float a_fAspectRatio, float a_fNear, float a_fFar)
				: Viewport(a_v3Pos, a_v3Rotation, a_v3Scale, PROJECTION_TYPE::PERSPECTIVE,
					glm::perspective(glm::radians(a_fDegreesFOV), a_fAspectRatio, a_fNear, a_fFar))
			{
				m_v2NearFar = { a_fNear, a_fFar };
				m_fFOV = a_fDegreesFOV;
				m_fAspectRatio = a_fAspectRatio;
			}

			PerspectiveViewport(glm::vec3 a_v3Pos, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, float a_fDegreesFOV, float a_fNear, float a_fFar)
				: PerspectiveViewport(a_v3Pos, a_v3Rotation, a_v3Scale, a_fDegreesFOV, (float)Window::getWidth() / (float)Window::getHeight(), a_fNear, a_fFar)
			{
			}

			virtual ~PerspectiveViewport()
			{
			}

			//resets the projection matrix
			void setProjectionMatrix(float a_fDegreesFOV, float a_fAspectRatio, float a_fNear, float a_fFar)
			{
				m_mat4Projection = glm::perspective(glm::radians(a_fDegreesFOV), a_fAspectRatio, a_fNear, a_fFar);
				m_fAspectRatio = a_fAspectRatio;
				m_fFOV = a_fDegreesFOV;
				m_v2NearFar = { a_fNear, a_fFar };
			}

			float getFOV() const
			{
				return m_fFOV;
			}

			float getAspectRatio() const
			{
				return m_fAspectRatio;
			}
		};
	}
}