#pragma once
#include "system/component_2d.h"

namespace ns_fretBuzz
{
	enum class  CANVAS_SPACE_TYPE
	{
		WORLD_SPACE = 0,
		SCREEN_SPACE_CAMERA = 1,
		SCREEN_SPACE_OVERLAY = 2,
	};

	struct CanvasData
	{
		CANVAS_SPACE_TYPE m_CanvasSpaceType = CANVAS_SPACE_TYPE::WORLD_SPACE;
		Camera* m_pCamera = nullptr;
		float m_fPlaneDistance = 0.0f;
	};

	class  Canvas : public IComponent2D
	{
	protected:
		virtual ~Canvas();

		///Camera component
		Camera* m_pCamera = nullptr;

		//The type of this canvas
		CANVAS_SPACE_TYPE m_CanvasType = CANVAS_SPACE_TYPE::WORLD_SPACE;

		float m_fPlaneDistance = 0.0f;

		//sets up the canvas with the type and camera
		//if its is world space then the camera will be forced to nullptr
		//else will required to be set
		void setupCanvas(CanvasData& a_CanvasData);

		virtual void lateUpdate(const float& a_fDeltaTime) override;

	public:
		Canvas(GameObject2D* a_GameObject2D, CanvasData& a_CanvasData, bool a_bIsEnabled = true);
	};
}