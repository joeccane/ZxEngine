#pragma once
#include "input_codes.hpp"
namespace zx::platform::windows
{
	int toGLFWKey(key k);
	int toGLFWMouseButton(mousebutton b);
	zx::key fromGLFWKey(int k);
	zx::mousebutton fromGLFWMouseButton(int b);
}