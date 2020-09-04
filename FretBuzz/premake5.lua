workspace "FretBuzz"
	architecture "x64"
	startproject "Sandbox"
		
	configurations
	{
		"Release",
		"Debug"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glm"] = "FretBuzzFramework/vendor/glm"
IncludeDir["ImGui"] = "FretBuzzFramework/vendor/imgui"
IncludeDir["GLFW"] = "FretBuzzFramework/vendor/glfw"
IncludeDir["spdlog"] = "FretBuzzFramework/vendor/spdlog"
IncludeDir["Box2D"] = "FretBuzzFramework/vendor/box2d"
IncludeDir["pugixml"] = "FretBuzzFramework/vendor/pugixml"

group "Dependencies"
	include "FretBuzzFramework/vendor/imgui"
	include "FretBuzzFramework/vendor/glfw"
	include "FretBuzzFramework/vendor/spdlog"
	include "FretBuzzFramework/vendor/box2d"
	include "FretBuzzFramework/vendor/pugixml"
group ""

project "FretBuzzFramework"
	location "FretBuzzFramework"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	architecture "x64"
	staticruntime "on"
	
	targetdir ("Bin/" .. outputdir .. "/%{prj.name}/Output" )
	objdir ("Bin/" .. outputdir .. "/%{prj.name}/Intermediates")
	
	pchheader "fretbuzz_pch.h"
	pchsource "FretBuzzFramework/framework/fretbuzz_pch.cpp"
	
	files
	{
		"%{prj.name}/main.h",
		"%{prj.name}/game_startup.h",
		"%{prj.name}/game_startup.cpp",
		"%{prj.name}/framework/**.h",
		"%{prj.name}/framework/**.cpp",
		"%{prj.name}/game/**.h",
		"%{prj.name}/game/**.cpp",
		"%{prj.name}/test/**.h",
		"%{prj.name}/test/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	
	includedirs
	{
		"%{IncludeDir.pugixml}/pugixml/src",
		"%{IncludeDir.spdlog}/spdlog/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/imgui",
		"%{IncludeDir.glm}/glm",
		"%{IncludeDir.GLFW}/glfw/include",
		"%{IncludeDir.Box2D}/box2d/include",
		"Libs",
		"Libs/GLEW",
		"Libs/FreeImage/include",
		"Libs/irrKlang/include",
		"Libs/Freetype/include",
		"Libs/assimp/include",
		"FretBuzzFramework",
		"FretBuzzFramework/vendor",
		"FretBuzzFramework/game",
		"FretBuzzFramework/framework",
		"FretBuzzFramework/framework/system"
	}

	libdirs
	{
		"Libs/GLEW/lib/x64",
		"Libs/FreeImage/lib/x64",
		"Libs/irrKlang/lib/x64",
		"Libs/Freetype/lib/x64"
	}
	
	links 
	{ 
		"pugixml",
		"Box2D",
		"ImGui",
		"GLFW",
		"spdlog",
		"opengl32.lib",
		"glew32s.lib",
		"FreeImage.lib",
		"irrKlang.lib",
		"freetype.lib",
		"assimp-vc140-mt.lib"
	}
	
	filter {"system:windows"}
		systemversion "latest"
		defines
		{
			"GLEW_STATIC",
			"_USE_MATH_DEFINES",
			"_IS_PLATFORM_WINDOWS",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter {"configurations:Debug"}
		runtime "Debug"
		symbols "on"
		libdirs
		{
			"Libs/assimp/lib/x64/Debug"
		}
		
	filter {"configurations:Release"}
		runtime "Release"
		optimize "on"
		libdirs
		{
			"Libs/assimp/lib/x64/Release"
		}
		
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}/Output" )
	objdir ("Bin/" .. outputdir .. "/%{prj.name}/Intermediates")

	files
	{
		"%{prj.name}/game/**.h",
		"%{prj.name}/game/**.cpp",
		"%{prj.name}/test/**.h",
		"%{prj.name}/test/**.cpp",
		"%{prj.name}/sandbox.cpp"
	}

	includedirs
	{
		"%{IncludeDir.pugixml}/pugixml/src",
		"%{IncludeDir.spdlog}/spdlog/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/imgui",
		"%{IncludeDir.glm}/glm",
		"%{IncludeDir.GLFW}/glfw/include",
		"%{IncludeDir.Box2D}/box2d/include",
		"Libs",
		"Libs/GLEW",
		"Libs/FreeImage/include",
		"Libs/irrKlang/include",
		"Libs/Freetype/include",
		"Libs/assimp/include",
		"FretBuzzFramework",
		"FretBuzzFramework/vendor",
		"FretBuzzFramework/game",
		"FretBuzzFramework/framework",
		"FretBuzzFramework/framework/system",
		"Sandbox"
	}

	links
	{
		"FretBuzzFramework"
	}
	
	postbuildcommands 
	{
		"{COPY} ../Libs/DLL/x64 %{cfg.targetdir}",
		"{COPY} resources %{cfg.targetdir}/resources"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"_IS_PLATFORM_WINDOWS",
			"_USE_MATH_DEFINES",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"