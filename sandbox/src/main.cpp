#include "zxengine.hpp"
#include <iostream>
struct testcom : zxAttribute(zx::component) {
	void awake() {
		std::cout << "AWAKE!\n";
	}
};
int main()
{
	auto app = new zx::application();
	auto scene = app->CreateScene<zx::scene>("TestScene");
	auto window = app->CreateWindow<zx::platform::windows::WindowsWindow>();

	auto e = scene->CreateEntity();

	e.AddComponent<testcom>();
	

	app->Run();
	
}