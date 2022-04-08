require "lua"

workspace "client"
	location ".\\build\\"

	targetdir "%{wks.location}\\bin\\%{cfg.buildcfg}\\"
	objdir "%{wks.location}\\obj\\%{cfg.buildcfg}\\%{prj.name}\\"
	buildlog "%{wks.location}\\obj\\%{cfg.buildcfg}\\%{prj.name}.log"

	vectorextensions "sse2"
	largeaddressaware "on"
	editandcontinue "off"
	staticruntime "on"

	systemversion "latest"
	characterset "mbcs"
	architecture "x86"
	warnings "extra"
	
	includedirs {
		".\\src\\",
	}

	buildoptions {
		"/Zm200",
		"/utf-8",
		"/std:c++17",
		"/bigobj",
	}

	flags {
		"noincrementallink",
		"no64bitchecks",
		"shadowedvariables",
		"undefinedidentifiers",
		"multiprocessorcompile",
	}

	defines {
		"NOMINMAX",
		"WIN32_LEAN_AND_MEAN",
		"_CRT_SECURE_NO_WARNINGS",
		"_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS",
	}

	platforms {
		"x86",
	}

	configurations {
		"Release",
		"Debug",
	}
	
	prebuildcommands {
		"cd ..\\tools\\",
		"call version.bat",
	}
	
	filter "Release"
		defines "NDEBUG"
		optimize "full"
		runtime "release"
		symbols "off"
	filter ""

	filter "Debug"
		defines "DEBUG"
		optimize "debug"
		runtime "debug"
		symbols "on"
	filter ""

	group "main"

	project "bootstrapper"
		targetname "rappy-bootstrapper-x86"
		language "c++"
		kind "consoleapp"
		warnings "off"	
		
		nuget {
			"sdl2.nuget:2.0.20",
			"sdl2.nuget.redist:2.0.20"
		}

		pchheader "stdafx.hpp"
		pchsource "src/game/stdafx.cpp"
		forceincludes "stdafx.hpp"
	
		postbuildcommands {
			"copy /y \"$(TargetPath)\" \"C:\\Games\\RappyLive\\\"",
		}

		links {
			"DbgHelp",
		}

		files {
			".\\src\\**",
		}

		includedirs {
			".\\src\\",
			".\\deps\\cpp-httplib\\",
			".\\deps\\ThemidaSDK\\include\\",
		}

		linkoptions {
			"/NXCOMPAT:NO",
			"/IGNORE:4254",
			"/DYNAMICBASE:NO",
			"/SAFESEH:NO",
			"/LARGEADDRESSAWARE",
			"/LAST:.main",
		}