#include "pch.hpp"
#include "platform/windows/WindowsWindow.hpp"
#include "application.hpp"
#include "debug.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
namespace zx::platform::windows
{
	void PrintError()
	{
		const char* desc;
		int code = glfwGetError(&desc);

		zxError(std::cout << code << ": " << desc << '\n');
	}
	GLFWwindow* GWindow(WindowsWindow* window)
	{
		return static_cast<GLFWwindow*>(window->nativeWindow());
	}
	void WindowsWindow::initialize()
	{
		
		pm_NativeWindow = glfwCreateWindow(640, 480, "TestWindow", NULL, NULL);
		if (!pm_NativeWindow)
			PrintError();

		glfwShowWindow(GWindow(this));

	}
	void WindowsWindow::update()
	{
		if (glfwWindowShouldClose(GWindow(this)))
			pm_ShouldClose = true;

		glfwSwapBuffers(GWindow(this));
		glfwWaitEvents();
	}
	void WindowsWindow::post_render()
	{
		if (pm_ShouldClose)
		{
			parent()->Remove(this);
		}
	}
	void WindowsWindow::exit()
	{	
		ReleaseSystem();
	}

	bool WindowsWindow::NativeInitialization()
	{
		if (!glfwInit())
		{
			PrintError();
			return false;
		}
		return true;
	}
	void WindowsWindow::NativeDispose()
	{
		glfwTerminate();
	}

}