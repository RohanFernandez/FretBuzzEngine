#pragma once

#pragma once

#ifdef _IS_DEBUG
	#ifndef _IS_DEBUG_RENDERING
		#define _IS_DEBUG_RENDERING
	#endif
#endif

#ifdef _IS_PLATFORM_WINDOWS
#ifdef _IS_FRETBUZZ_BUILD_DLL
#endif
#else
#endif

/// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
/// Math

/// Utils
#include <log/log.h>
/// Utils

/////Gameobject Components
//#include <components/gameobject_components/audio_source.h>
//#include <components/gameobject_components/behaviour.h>
//#include <components/gameobject_components/camera.h>
//#include <components/gameobject_components/canvas.h>
//#include <components/gameobject_components/character_controller_2d.h>
//#include <components/gameobject_components/image.h>
//#include <components/gameobject_components/light.h>
//#include <components/gameobject_components/mesh_renderer.h>
//#include <components/gameobject_components/rect_collider.h>
//#include <components/gameobject_components/sprite_animation_controller.h>
//#include <components/gameobject_components/sprite_renderer.h>
//#include <components/gameobject_components/text_renderer.h>
/////Gameobject Components
//
/////Components
//#include <components/audio_clip.h>
//#include <components/collider_2d.h>
//#include <components/collider_data.h>
//#include <components/raycast_callback.h>
//#include <components/rect_transform.h>
//#include <components/sprite.h>
//#include <components/sprite_animator.h>
//#include <components/transform.h>
//#include <components/viewport.h>
/////Components
//
/////Graphics
//#include <graphics/batch_renderer_manager.h>
////#include <graphics/light_batch_renderer.h>
//#include <graphics/data_texture.h>
//#include <graphics/font.h>
//#include <graphics/font_manager.h>
//#include <graphics/light_manager.h>
//#include <graphics/material.h>
//#include <graphics/mesh.h>
//#include <graphics/model.h>
//#include <graphics/post_process_manager.h>
//#include <graphics/rect.h>
//#include <graphics/renderer.h>
//#include <graphics/shader.h>
//#include <graphics/shader_factory.h>
//#include <graphics/shader_manager.h>
//#include <graphics/sprite_batch_renderer.h>
//#include <graphics/texture.h>
/////Graphics
//
/////System
//#include <system/core/asset_loader.h>
//#include <system/core/audio_engine.h>
//#include <system/core/input.h>
//#include <system/core/managed_resource.h>
//#include <system/core/master_renderer.h>
//#include <system/core/physics_engine.h>
//#include <system/core/resource_manager.h>
//#include <system/core/system.h>
//#include <system/core/window.h>
//#include <system/core/layer/layer.h>
//#include <system/core/layer/layer_manager.h>
//#include <system/core/layer/layer_mask.h>
//
//#include <system/camera_manager.h>
//#include <system/component.h>
//#include <system/component_2d.h>
//#include <system/game_object.h>
//#include <system/game_object_2d.h>
//#include <system/game_startup_data.h>
//#include <system/scene_manager.h>
/////System
//
/////Utils
//#include <utils/file_utils.h>
//#include <utils/FSM.h>
//#include <utils/resource_container.h>
//#include <utils/Event/Delegate/delegate.h>
//#include <utils/pool/object_pool.h>
//#include <utils/pool/gameobject_pool.h>
/////Utils
