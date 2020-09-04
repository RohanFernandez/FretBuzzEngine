#pragma once
#include <window.h>
#include "transform.h"
#include <imgui/imgui.h>

namespace FRETBUZZ
{
	class  Viewport
	{
	public:
		enum class PROJECTION_TYPE
		{
			ORTHOGRAPHIC,
			PERSPECTIVE
		};

	protected:
		PROJECTION_TYPE m_ProjectionType;
		glm::mat4 m_mat4Projection = glm::mat4{ 1.0f };
		glm::mat4 m_mat4View = glm::mat4{1.0f};

		Viewport() = delete;
		Viewport(PROJECTION_TYPE a_ProjectionType, glm::mat4 a_mat4Projection, glm::vec2 a_v2OriginXY, glm::vec2 a_v2DimensionWH01);
		glm::vec2 m_v2NearFar = { 0.0f, 1.0f };
		glm::vec2 m_v2OriginXY01 = {0.0f, 0.0f};
		glm::vec2 m_v2DimensionWH01 = { 0.0f, 0.0f };

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

		const glm::vec2& getOriginXY01() const
		{
			return m_v2OriginXY01;
		}

		glm::vec2 getOriginXY() const
		{
			return { m_v2OriginXY01.x * Window::getWidth() , m_v2OriginXY01.y * Window::getHeight() };
		}

		const glm::vec2& getDimensionWH01() const
		{
			return m_v2DimensionWH01;
		}

		glm::vec2 getDimensionWH() const
		{
			return { m_v2DimensionWH01.x * Window::getWidth() , m_v2DimensionWH01.y * Window::getHeight() };
		}

		virtual void editorInspectorRender()
		{
			bool l_bIsResetProjectionMatrix = false;

			float l_fArr[2] = {};

			//Near Far
			l_fArr[0] = m_v2NearFar.x;
			l_fArr[1] = m_v2NearFar.y;
			ImGui::Text("Near Far "); ImGui::SameLine(120);
			if (ImGui::InputFloat2("##NearFar", l_fArr, 1))
			{
				m_v2NearFar.x = l_fArr[0];
				m_v2NearFar.y = l_fArr[1];
				l_bIsResetProjectionMatrix = true;
			}

			//Origin X Y
			l_fArr[0] = m_v2OriginXY01.x;
			l_fArr[1] = m_v2OriginXY01.y;
			ImGui::Text("XY "); ImGui::SameLine(120);
			if (ImGui::InputFloat2("##XY", l_fArr, 1))
			{
				m_v2OriginXY01.x = l_fArr[0];
				m_v2OriginXY01.y = l_fArr[1];
				l_bIsResetProjectionMatrix = true;
			}

			//Dimension width - height
			l_fArr[0] = m_v2DimensionWH01.x;
			l_fArr[1] = m_v2DimensionWH01.y;
			ImGui::Text("WH "); ImGui::SameLine(120);
			if (ImGui::InputFloat2("##WH", l_fArr, 1))
			{
				m_v2DimensionWH01.x = l_fArr[0];
				m_v2DimensionWH01.y = l_fArr[1];
				l_bIsResetProjectionMatrix = true;
			}

			if (l_bIsResetProjectionMatrix)
			{
				resetProjectionMatrix();
			}
		}

		virtual void resetProjectionMatrix() = 0;
	};

	class OrthographicViewport : public Viewport
	{
	protected:
		glm::vec2 m_v2LeftRight;
		glm::vec2 m_v2BottomTop;

	public:
		OrthographicViewport(float a_fleft, float a_fRight, float a_fBottom, float a_fTop, float a_fNear, float a_fFar, glm::vec2 a_v2OriginXY01, glm::vec2 a_v2DimensionWH01)
			: Viewport(PROJECTION_TYPE::ORTHOGRAPHIC,
				glm::ortho(a_fleft * (float)Window::getWidth(), a_fRight * (float)Window::getWidth(), a_fBottom * (float)Window::getHeight(), a_fTop * (float)Window::getHeight(), a_fNear, a_fFar), a_v2OriginXY01, a_v2DimensionWH01)
		{
			setProjectionMatrix(a_fleft, a_fRight, a_fBottom, a_fTop, a_fNear, a_fFar);
		}

		OrthographicViewport(float a_fNear, float a_fFar)
			: OrthographicViewport(-0.5f, 0.5f, -0.5f, 0.5f, a_fNear, a_fFar, { 0.0f,0.0f }, {1.0f, 1.0f })
		{	
		}

		virtual ~OrthographicViewport()
		{
		}

		//resets the projection matrix
		void setProjectionMatrix(float a_fLeft, float a_fRight, float a_fBottom, float a_fTop, float a_fNear, float a_fFar)
		{
			m_v2BottomTop = {a_fBottom, a_fTop};
			m_v2LeftRight = { a_fLeft, a_fRight};
			m_v2NearFar = { a_fNear, a_fFar };
			resetProjectionMatrix();
		}

		virtual void resetProjectionMatrix() override
		{
			m_mat4Projection = glm::ortho(m_v2LeftRight.x * (float)Window::getWidth(), m_v2LeftRight.y * (float)Window::getWidth(), m_v2BottomTop.x * (float)Window::getHeight(), m_v2BottomTop.y * (float)Window::getHeight(), m_v2NearFar.x, m_v2NearFar.y);
		}

		const glm::vec2& getBottomTop() const
		{
			return m_v2BottomTop;
		}

		const glm::vec2& getLeftRight() const
		{
			return m_v2LeftRight;
		}

		virtual void editorInspectorRender() override
		{
			Viewport::editorInspectorRender();

			bool l_bIsResetProjectionMatrix = false;

			float l_fArr[2] = {};

			//Left Right
			l_fArr[0] = m_v2LeftRight.x;
			l_fArr[1] = m_v2LeftRight.y;
			ImGui::Text("Left Right "); ImGui::SameLine(120);
			if (ImGui::InputFloat2("##LeftRight", l_fArr, 1))
			{
				m_v2LeftRight.x = l_fArr[0];
				m_v2LeftRight.y = l_fArr[1];
				l_bIsResetProjectionMatrix = true;
			}

			//bottom top
			l_fArr[0] = m_v2BottomTop.x;
			l_fArr[1] = m_v2BottomTop.y;
			ImGui::Text("Bottom Top "); ImGui::SameLine(120);
			if(ImGui::InputFloat2("##BottomTop", l_fArr, 1))
			{
				m_v2BottomTop.x = l_fArr[0];
				m_v2BottomTop.y = l_fArr[1];
				l_bIsResetProjectionMatrix = true;
			}

			if (l_bIsResetProjectionMatrix)
			{
				resetProjectionMatrix();
			}

		}
	};

	class PerspectiveViewport : public Viewport
	{
	protected:
		float m_fFOV = 0.0f;
		float m_fAspectRatio = 0.0f;

	public:
		PerspectiveViewport(float a_fDegreesFOV, float a_fNear, float a_fFar, glm::vec2 a_v2OriginXY01, glm::vec2 a_v2DimensionWH01)
			: Viewport(PROJECTION_TYPE::PERSPECTIVE,
				glm::perspective(glm::radians(a_fDegreesFOV), (a_v2DimensionWH01.x * (float)Window::getWidth())/ (a_v2DimensionWH01.y * (float)Window::getHeight()), a_fNear, a_fFar), a_v2OriginXY01, a_v2DimensionWH01)
		{
			setProjectionMatrix(a_fDegreesFOV, a_fNear, a_fFar, m_v2DimensionWH01);
		}

		PerspectiveViewport(float a_fDegreesFOV, float a_fNear, float a_fFar)
			: PerspectiveViewport(a_fDegreesFOV, a_fNear, a_fFar, {0.0f, 0.0f}, {1.0f, 1.0f })
		{
		}

		virtual ~PerspectiveViewport()
		{
		}

		//resets the projection matrix
		void setProjectionMatrix(float a_fDegreesFOV, float a_fNear, float a_fFar, glm::vec2 a_v2DimensionWH01)
		{
			m_fFOV = a_fDegreesFOV;
			m_v2NearFar = { a_fNear, a_fFar }; 
			m_v2DimensionWH01 = a_v2DimensionWH01;
			resetProjectionMatrix();
		}

		virtual void resetProjectionMatrix() override
		{
			const glm::vec2& l_v2DimensionWH = getDimensionWH();
			m_fAspectRatio = (l_v2DimensionWH.x) / (l_v2DimensionWH.y);
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

		virtual void editorInspectorRender() override
		{
			Viewport::editorInspectorRender();

			bool l_bIsResetProjectionMatrix = false;

			//sets FOV
			ImGui::Text("FOV "); ImGui::SameLine(120);
			if (ImGui::InputFloat("##FOV", &m_fFOV, 1))
			{
				l_bIsResetProjectionMatrix = true;
			}

			//sets aspect ratio
			ImGui::Text("Aspect Ratio "); ImGui::SameLine(120);
			if (ImGui::InputFloat("##AspectRatio", &m_fAspectRatio, 1))
			{
				l_bIsResetProjectionMatrix = true;
			}

			if (l_bIsResetProjectionMatrix)
			{
				resetProjectionMatrix();
			}
		}
	};
}