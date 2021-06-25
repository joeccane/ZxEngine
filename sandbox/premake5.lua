project "sandbox"
	kind "ConsoleApp"
	cppdialect "C++20"
	staticruntime "on"

	files{
		"include/**.h",
		"include/**.hpp",
		"include/**.c",
		"include/**.cpp",

		"src/**.h",
		"src/**.hpp",
		"src/**.c",
		"src/**.cpp"
	}

	includedirs{
		"include",
		"%{wks.location}/zxengine-core/include",
		"%{wks.location}/zxengine-core/vendor/glm",
		"%{wks.location}/zxengine-core/vendor",
		"%{wks.location}/zxengine-core/vendor/vendor/glm",
	}
	links{
		"zxengine-core"
	}
	filter "system:windows"
		systemversion "latest"

		defines{
			"ZX_PLATFORM_WINDOWS"
		}
	filter "configurations:Debug"
		defines{
			"ZX_DEBUG"
		}
	filter "configurations:Release"
		defines{
			"ZX_RELEASE"
		}
		optimize "on"
	filter "configurations:Dist"
		defines{
			"ZX_DIST"
		}
		optimize "on"
