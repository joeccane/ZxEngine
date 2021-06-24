#include "pch.hpp"

#include <iostream>
#include <chrono>
#include <string>

#include "zxengine.hpp"

int main()
{
	zx::application* app = new zx::application();
	zx::scene* scene = app->CreateScene<zx::scene>("main");

	app->Run();

	delete app;

}