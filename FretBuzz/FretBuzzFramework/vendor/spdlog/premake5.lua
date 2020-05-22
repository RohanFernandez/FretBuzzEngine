project "spdlog"
	kind "StaticLib"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Bin/" .. outputdir .. "/%{prj.name}")

	files
	{
		"spdlog/include/spdlog/**.h",
		"spdlog/src/**.cpp"
	}
	
	includedirs
	{
		"spdlog/include/"
	}

	filter "system:windows"
		systemversion "latest"
		defines 
		{ 
			"SPDLOG_COMPILED_LIB"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
