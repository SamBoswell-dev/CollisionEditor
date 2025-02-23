workspace "CollisionEditor"
	architecture "x86"
	configurations { "Debug", "Release"}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"	
	
project "CollisionEditor"
	location "CollisionEditor"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"vendor/cJSON/cJSON.c",
		"vendor/tinyfiledialog/tinyfiledialogs.c"
	}
	
	includedirs
	{
		"vendor/Raylib/include",
		"vendor/raygui/include",
		"vendor/cJSON/include",
		"vendor/tinyfiledialog/include"
	}
	
	libdirs { "vendor/Raylib/lib" }
	
	links { "raylib.lib", "Winmm.lib" }
	
	cppdialect "C++17"
	staticruntime "Off"
	systemversion "latest"
	
	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"