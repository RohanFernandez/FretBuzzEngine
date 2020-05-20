project "pugixml"
	location "pugixml"
	kind "StaticLib"
	cppdialect "C++17"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Bin/" .. outputdir .. "/%{prj.name}")

	files
	{
		"pugixml/src/**.hpp",
		"pugixml/src/**.cpp"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
