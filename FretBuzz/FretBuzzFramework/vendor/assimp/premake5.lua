project "assimp"
	kind "StaticLib"
	language "C++"

	targetdir ("Bin/" .. outputdir .. "/%{prj.name}")
	objdir ("Bin/" .. outputdir .. "/%{prj.name}")

	files
	{
		"assimp/include/**.h",
		"assimp/include/**.hpp",
		"assimp/include/**.inl",
		"assimp/code/**.h",
		"assimp/code/**.hpp",
		"assimp/code/**.cpp"
	}
	
	includedirs
	{
		"assimp/include/"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
