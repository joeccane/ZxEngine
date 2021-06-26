#include "zxengine.hpp"
int main()
{
	auto app = new zx::application();
	auto scene = app->CreateScene<zx::scene>("TestScene");
	auto window = app->CreateWindow<zx::platform::windows::WindowsWindow>();

	app->Run();
}