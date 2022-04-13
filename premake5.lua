workspace "Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "Engine/vendor/imgui"
IncludeDir["glm"] = "Engine/vendor/glm"
IncludeDir["stb_image"] = "Engine/vendor/stb_image"
IncludeDir["ImGuizmo"] = "Engine/vendor/ImGuizmo"
IncludeDir["yaml_cpp"] = "Engine/vendor/yaml-cpp/include"
IncludeDir["assimp"] = "Engine/vendor/assimp/include"

include "Engine/vendor/GLFW"
include "Engine/vendor/Glad"
include "Engine/vendor/imgui"
include "Engine/vendor/yaml-cpp"

project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir("bin/"..outputdir.."/%{prj.name}")
	objdir("bin-int/"..outputdir.."/%{prj.name}")

	-- pchheader "Engine/EEpch.h"
	-- pchsource "src/Engine/EEpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp",
		-- "%{prj.name}/vendor/assimp/**.h",
		-- "%{prj.name}/vendor/assimp/**.hpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"YAML_CPP_STATIC_DEFINE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.assimp}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"Engine/vendor/assimp/bin/Debug/assimp-vc142-mtd.lib",
		--"Engine/vendor/assimp/bin/Debug",
		"opengl32.lib"
	}


	filter "files:vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"ENGINE_PLATFORM_WINDOWS",
		"ENGINE_BUILD_DLL"
	}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		symbols "On"

	filter "configurations.Release"
		defines "ENGINE_RELEASE"
		optimize "On"




project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}


	includedirs
	{
		"Engine/src",
		"Engine/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.assimp}"
	}

	links
	{
		"Engine"
	}

	postbuildcommands
	{
		'{COPY} "Engine/vendor/assimp/bin/Debug/assimp-vc142-mtd.dll" "%{cfg.targetdir}"'
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
		"ENGINE_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		symbols "On"

	filter "configurations.Release"
		defines "ENGINE_RELEASE"
		optimize "On"