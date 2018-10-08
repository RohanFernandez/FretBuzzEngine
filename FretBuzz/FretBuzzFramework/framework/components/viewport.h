#pragma once
#include "../system/core/window.h"
#include "transform.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
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
			Viewport(PROJECTION_TYPE a_ProjectionType, glm::mat4 a_mat4Projection);
			glm::vec2 m_v2NearFar = {};


		public:
			virtual ~Viewport() = 0 {};

			//Returns projection type i.e orthographic / perspective.
			inline PROJECTION_TYPE getProjectionType() const
			{
				return m_ProjectionType;
			}

			inline const glm::mat4 getProjectionMatrix() const
			{
				return m_mat4Projection;
			}

			const glm::vec2& getNearFar() const
			{
				return m_v2NearFar;
			}

			virtual void resetProjectionMatrix() = 0;
		};

		class OrthographicViewport : public Viewport
		{
		protected:
			glm::vec2 m_v2LeftRight;
			glm::vec2 m_v2BottomTop;

		public:
			OrthographicViewport(float a_fleft, float a_fRight, float a_fBottom, float a_fTop, float a_fNear, float a_fFar)
				: Viewport(PROJECTION_TYPE::ORTHOGRAPHIC,
					glm::ortho(a_fleft * Window::getWidth(), a_fRight * Window::getWidth(), a_fBottom * Window::getHeight(), a_fTop * Window::getHeight(), a_fNear, a_fFar))
			{
				m_v2NearFar = { a_fNear, a_fFar };
				m_v2LeftRight = { a_fleft, a_fRight };
				m_v2BottomTop = { a_fBottom , a_fTop };
			}

			OrthographicViewport(float a_fNear, float a_fFar)
				: OrthographicViewport(-0.5f, 0.5f, -0.5f, 0.5f, a_fNear, a_fFar)
			{	
			}

			virtual ~OrthographicViewport()
			{
			}

			//resets the projection matrix
			void setProjectionMatrix(float a_fLeft, float a_fRight, float a_fBottom, float a_fTop, float a_fNear, float a_fFar)
			{
				float l_fWindowWidth = Window::getWidth();
				float l_fWindowHeight = Window::getHeight();

				m_v2BottomTop = {a_fBottom, a_fTop};
				m_v2LeftRight = { a_fLeft, a_fRight};
				m_v2NearFar = { a_fNear, a_fFar };
				m_mat4Projection = glm::ortho(a_fLeft * l_fWindowWidth, a_fRight * l_fWindowWidth, a_fBottom * l_fWindowHeight, a_fTop * l_fWindowHeight, a_fNear, a_fFar);
			}

			virtual void resetProjectionMatrix() override
			{
				float l_fWindowWidth = Window::getWidth();
				float l_fWindowHeight = Window::getHeight();
				m_mat4Projection = glm::ortho(m_v2LeftRight.x * l_fWindowWidth, m_v2LeftRight.y * l_fWindowWidth, m_v2BottomTop.x * l_fWindowHeight, m_v2BottomTop.y * l_fWindowHeight, m_v2NearFar.x, m_v2NearFar.y);
			}

			const glm::vec2& getBottomTop() const
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
			PerspectiveViewport(float a_fDegreesFOV, float a_fAspectRatio, float a_fNear, float a_fFar)
				: Viewport(PROJECTION_TYPE::PERSPECTIVE,
					glm::perspective(glm::radians(a_fDegreesFOV), a_fAspectRatio, a_fNear, a_fFar))
			{
				m_v2NearFar = { a_fNear, a_fFar };
				m_fFOV = a_fDegreesFOV;
				m_fAspectRatio = a_fAspectRatio;
			}

			PerspectiveViewport(float a_fDegreesFOV, float a_fNear, float a_fFar)
				: PerspectiveViewport(a_fDegreesFOV, (float)Window::getWidth() / (float)Window::getHeight(), a_fNear, a_fFar)
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

			virtual  void resetProjectionMatrix() override
			{
				m_fAspectRatio = Window::getAspectRatio();
				m_mat4Projection = glm::perspective(glm::radians(m_fFOV), m_fAspectRatio, m_v2NearFar.x, m_v2NearFar.y);
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