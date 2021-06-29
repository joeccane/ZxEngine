#pragma once
namespace zx
{
	enum class WindowAPI {
		none,
		glfw
	};
	enum class GraphicsAPI {
		none,
		opengl
	};

	struct PlatformSelector 
	{
		PlatformSelector(WindowAPI window, GraphicsAPI graphics)
			: window(window), graphics(graphics) {}
		WindowAPI window;
		GraphicsAPI graphics;
	};
}