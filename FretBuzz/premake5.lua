workspace "FretBuzz"
	architecture "x64"
	startproject "FretBuzzFramework"
		
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
IncludeDir["Box2D"] = "FretBuzzFramework/vendor/Box2D"

group "Dependencies"
	include "FretBuzzFramework/vendor/imgui"
	include "FretBuzzFramework/vendor/glfw"
	include "FretBuzzFramework/vendor/spdlog"
	include "FretBuzzFramework/vendor/Box2D"
group ""

project "FretBuzzFramework"
	location "FretBuzzFramework"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	architecture "x64"
	-- staticruntime "on"
	
	targetdir ("Bin/" .. outputdir .. "/%{prj.name}/Output" )
	objdir ("Bin/" .. outputdir .. "/%{prj.name}/Intermediates")
	
	pchheader "fretbuzz_pch.h"
	pchsource "FretBuzzFramework/framework/fretbuzz_pch.cpp"
	
	files
	{
		"%{prj.name}/main.cpp",
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
		"%{IncludeDir.spdlog}/include",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLFW}/include",
		"%{IncludeDir.Box2D}/include",
		"Libs",
		"Libs/GLEW",
		"Libs/FreeImage/include",
		"Libs/irrKlang/include",
		"Libs/Freetype/include",
		"Libs/pugixml/include",
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
		"Box2D",
		"ImGui",
		"GLFW",
		"spdlog",
		"opengl32.lib",
		"glew32s.lib",
		"FreeImage.lib",
		"irrKlang.lib",
		"freetype.lib",
		"pugixml.lib",
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
		
		postbuildcommands 
		{
			"{COPY} ../Libs/DLL/x64 %{cfg.targetdir}",
			"{COPY} resources %{cfg.targetdir}/resources"
		}
		
	filter {"configurations:Debug"}
		defines "_IS_DEBUG"
		runtime "Debug"
		symbols "on"
		libdirs
		{
			"Libs/Box2D/lib/x64/Debug",
			"Libs/pugixml/lib/x64/Debug",
			"Libs/assimp/lib/x64/Debug"
		}
		
	filter {"configurations:Release"}
		runtime "Release"
		optimize "on"
		libdirs
		{
			"Libs/Box2D/lib/x64/Release",
			"Libs/pugixml/lib/x64/Release",
			"Libs/assimp/lib/x64/Release"
		}
		
		
project "Sandbox"
	location "Sandbox"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}/Output" )
	objdir ("Bin/" .. outputdir .. "/%{prj.name}/Intermediates")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs
	{
		"FretBuzzFramework",
		"FretBuzzFramework/framework",
		-- "Hazel/vendor/spdlog/include",
		-- "Hazel/src",
		-- "Hazel/vendor",
		-- "%{IncludeDir.glm}"
	}

	links
	{
		--"FretBuzzFramework"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"