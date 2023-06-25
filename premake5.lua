workspace "Tsukasa-Tsukuyomi"
	architecture "x64"
	configurations { "Release" }

project "Tsukasa-Tsukuyomi"
	kind          "ConsoleApp"
	language      "C++"
	cppdialect    "C++17"
	staticruntime "off"

	outputdir = "%{cfg.buildcfg}"

	targetdir ("%{wks.location}/x64/%{cfg.buildcfg}")
	objdir    ("%{wks.location}/x64/%{cfg.buildcfg}")

	includedirs{ "include", "handler" }
	libdirs    { "lib" }
	links      { "dpp.lib", "opencv_world470d.lib" }
	files      { 
		"src/**.cpp", 
		"src/cmd_lists/cmd_common/**.cpp",
        "src/cmd_lists/cmd_moderation/**.cpp",
        "src/cmd_engine/**.cpp",
		"handler/**.h",
        "handler/cmd_builder/**.h",
		"Tsukasa Tsukuyomi.rc",
        "resource.h"
	}

	filter { "system:windows", "toolset:msc" }
		systemversion "latest"

	filter "configurations:Release"
		runtime  "Release"
		optimize "on"
