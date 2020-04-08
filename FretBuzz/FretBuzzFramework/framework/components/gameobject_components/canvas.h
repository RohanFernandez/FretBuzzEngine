#pragma once
#include "system/component_2d.h"

namespace ns_fretBuzz
{
	namespace ns_UI
	{
		enum class FRETBUZZ_API CANVAS_SPACE_TYPE
		{
			WORLD_SPACE = 0,
			SCREEN_SPACE_CAMERA = 1,
			SCREEN_SPACE_OVERLAY = 2,
		};

		struct CanvasData
		{
			CANVAS_SPACE_TYPE m_CanvasSpaceType = CANVAS_SPACE_TYPE::WORLD_SPACE;
			ns_graphics::Camera* m_pCamera = nullptr;
			float m_fPlaneDistance = 0.0f;
		};

		class FRETBUZZ_API Canvas : public ns_system::IComponent2D
		{
		protected:
			Canvas(ns_system::GameObject2D& a_GameObject2D, CanvasData& a_CanvasData, bool a_bIsEnabled = true);
			virtual ~Canvas();

			///Camera component
			ns_graphics::Camera* m_pCamera = nullptr;

			//The type of this canvas
			CANVAS_SPACE_TYPE m_CanvasType = CANVAS_SPACE_TYPE::WORLD_SPACE;

			float m_fPlaneDistance = 0.0f;

			//sets up the canvas with the type and camera
			//if its is world space then the camera will be forced to nullptr
			//else will required to be set
			void setupCanvas(CanvasData& a_CanvasData);

			virtual void lateUpdate(float a_fDeltaTime) override;

		public:
			static Canvas* addToGameObject(ns_system::GameObject2D& a_GameObject2D, CanvasData& a_CanvasData, bool a_bIsEnabled = true);
		};
	}
}