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

project "FretBuzzFramework"
	location "FretBuzzFramework"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	architecture "x64"
	
	targetdir ("Bin/" .. outputdir .. "/%{prj.name}" )
	objdir ("Bin/" .. outputdir .. "/Intermediates")
	
	pchheader "fretbuzz_pch.h"
	pchsource "FretBuzzFramework/fretbuzz_pch.cpp"
	
	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"%{prj.name}/**.hpp",
		"%{prj.name}/**.xml"
	}
	
	includedirs
	{
		"Libs",
		"Libs/GLFW",
		"Libs/GLEW",
		"Libs/FreeImage/include",
		"Libs/GLM/include",
		"Libs/irrKlang/include",
		"Libs/Freetype/include",
		"Libs/Box2D/include",
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
		"Libs/GLFW/lib/x64",
		"Libs/GLEW/lib/x64",
		"Libs/FreeImage/lib/x64",
		"Libs/irrKlang/lib/x64",
		"Libs/Freetype/lib/x64"
	}
	
	links 
	{ 
		"opengl32.lib",
		"glfw3.lib",
		"glew32s.lib",
		"FreeImage.lib",
		"irrKlang.lib",
		"freetype.lib",
		"Box2D.lib",
		"pugixml.lib",
		"assimp-vc140-mt.lib"
	}
	
	filter {"system:windows"}
		systemversion "latest"
		defines
		{
			"GLEW_STATIC",
			"_USE_MATH_DEFINES",
			"_FRETBUZZ_WINDOWS",
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