project "box2d"
	kind "StaticLib"
	language "C++"
	staticruntime "on"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Bin/" .. outputdir .. "/%{prj.name}")

	files
	{
		"box2d/include/Box2d/**.h",
		"box2d/src/**.h",
		"box2d/src/**.cpp"
	}
	
	includedirs
	{
		"box2d/src/",
		"box2d/include/"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
