#include "zxengine.hpp"
int main()
{
	auto app = new zx::application();
	auto scene = app->CreateScene<zx::scene>("TestScene");
	auto window = app->CreateWindow<zx::platform::windows::WindowsWindow>();
	zx::subscriber_id id = window->onFocus() << [](zx::WindowFocusEventData& data) {
		if (data.focused)
			std::cout << "Focused!\n";
		else std::cout << "No Focus!\n";
	};
	auto id2 = window->onMouseMoved() << [](zx::MouseMovedEventData& data) {
		std::cout << std::to_string(data.delta().x) << ", " << std::to_string(data.delta().y) << '\n';
	};
	app->Run();
	
}