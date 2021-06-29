--zx core---------------------

project "zxengine-core"
	kind "StaticLib"
	cppdialect "C++20"
	staticruntime "on"

	pchheader "pch.hpp"
	pchsource "pch.cpp"

	files{

		"pch.hpp",
		"pch.cpp",


		"include/**.h",
		"include/**.hpp",
		"include/**.c",
		"include/**.cpp",

		"src/**.h",
		"src/**.hpp",
		"src/**.c",
		"src/**.cpp",

		"vendor/vendor/entt.hpp",
		"vendor/vendor/glm/vendor/**.h",
		"vendor/vendor/glm/vendor/**.hpp",
		"vendor/vendor/glm/vendor/**.c",
		"vendor/vendor/glm/vendor/**.cpp",
		"vendor/vendor/glm/vendor/**.inl",

		"vendor/vendor/glad/include/**.h",
		"vendor/vendor/glad/src/**.cpp"

	}
	includedirs{
		"",
		"include",
		"vendor",
		"vendor/vendor/glm",
		"%{wks.location}/glfw/include",
		"vendor/vendor/glad/include"
	}
	links{
		"glfw", "opengl32"
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