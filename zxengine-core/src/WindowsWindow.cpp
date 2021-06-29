#include "pch.hpp"
#include "platform/windows/WindowsWindow.hpp"
#include "application.hpp"
#include "debug.hpp"
#include <iostream>
#include "platform/windows/WindowInputCodeConvert.hpp"
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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		pm_NativeWindow = glfwCreateWindow(pm_Options.size.width, pm_Options.size.height, pm_Options.title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(GWindow(this));

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			zxFatalAssert(false, "Could not load OpenGL")
		}
		glClearColor(1.0f, 0.25f, 1.0f, 1.0f);
		if (!pm_NativeWindow)
			PrintError();
		glfwSetWindowUserPointer(GWindow(this), this);

		//hook events
		glfwSetKeyCallback(GWindow(this), [](GLFWwindow* window, int key, int scancode, int action, int mods) {

			WindowsWindow* w = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
			if (action == GLFW_PRESS)
			{
				KeyPressedEventData data = KeyPressedEventData(zx::platform::windows::fromGLFWKey(key), false);
				data.key = fromGLFWKey(key);
				w->pm_KeyPressedEvent.Enqueue(data);
			}
			else if (action == GLFW_RELEASE)
			{
				KeyReleasedEventData data = KeyReleasedEventData(zx::platform::windows::fromGLFWKey(key));
				w->pm_KeyReleasedEvent.Enqueue(data);
			}
			else if (action == GLFW_REPEAT)
			{
				KeyPressedEventData data = KeyPressedEventData(zx::platform::windows::fromGLFWKey(key), true);
				w->pm_KeyPressedEvent.Enqueue(data);
			}
			});
		glfwSetMouseButtonCallback(GWindow(this), [](GLFWwindow* window, int button, int action, int mods) {
			WindowsWindow* w = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

			if (action == GLFW_PRESS)
			{
				MouseButtonEventData data = MouseButtonEventData();
				data.button = fromGLFWMouseButton(button);
				data.handled = false;
				data.action = buttonAction::pressed;
				w->pm_MouseButtonPressedEvent.Enqueue(data);
			}
			if (action == GLFW_PRESS)
			{
				MouseButtonEventData data;
				data.button = fromGLFWMouseButton(button);
				data.handled = false;
				data.action = buttonAction::released;
				w->pm_MouseButtonReleasedEvent.Enqueue(data);
			}
			});
		glfwSetCursorPosCallback(GWindow(this), [](GLFWwindow* window, double xpos, double ypos) {
			WindowsWindow* w = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
			MouseMovedEventData data = MouseMovedEventData(w->pm_PrevMousePos, vector2(static_cast<float>(xpos), static_cast<float>(ypos)));
			w->pm_MouseMovedEvent.Enqueue(data);
			});
		glfwSetScrollCallback(GWindow(this), [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowsWindow* w = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

			ScrollEventData e = ScrollEventData(vector2(static_cast<float>(xoffset), static_cast<float>(yoffset)));
			w->pm_ScrollEvent.Enqueue(e);
			});
		glfwSetWindowFocusCallback(GWindow(this), [](GLFWwindow* window, int focus) {
			WindowsWindow* w = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
			bool focused = focus == GLFW_TRUE;
			OnFocusEventData<zx::window> data;
			data.focused = focused;
			data.sender = w;
			data.handled = false;

			w->pm_OnFocusEvent.Enqueue(data);
			});
		glfwShowWindow(GWindow(this));

	}
	vector2 WindowsWindow::mousePos()
	{
		double x, y;
		glfwGetCursorPos(GWindow(this), &x, &y);
		return vector2(static_cast<float>(x), static_cast<float>(y));
	}
	void WindowsWindow::update()
	{
		if (glfwWindowShouldClose(GWindow(this)))
			pm_ShouldClose = true;

	}
	void WindowsWindow::late_update()
	{
		pm_KeyPressedEvent.InvokeAll([=](KeyPressedEventData& data) {
			KeyEventData& keyEventData = data;
			pm_KeyEvent.Invoke(keyEventData);
			});
		pm_KeyReleasedEvent.InvokeAll([=](KeyReleasedEventData& data) {
			KeyEventData& keyEventData = data;
			pm_KeyEvent.Invoke(keyEventData);
			});
		pm_MouseButtonPressedEvent.InvokeAll();
		pm_MouseButtonReleasedEvent.InvokeAll();
		pm_ScrollEvent.InvokeAll();
		pm_OnFocusEvent.InvokeAll();
		pm_OnDisposeEvent.InvokeAll();

		pm_MouseMovedEvent.InvokeAll();
		pm_PrevMousePos = mousePos();
	}
	void WindowsWindow::pre_render()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void WindowsWindow::post_render()
	{
		glfwSwapBuffers(GWindow(this));
		glfwPollEvents();
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