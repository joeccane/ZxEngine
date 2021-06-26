
//our input codes are based off of GLFW input codes, so conversion is trivial
#include "pch.hpp"
#include "platform/windows/WindowInputCodeConvert.hpp"



namespace zx::platform::windows
{
	int toGLFWKey(key k)
	{
		if (k.code->value == key::none.value)
			return -1;

		return static_cast<int>(k.code->value);
	}
	int toGLFWMouseButton(mousebutton b)
	{
		return static_cast<int>(b.code->value - 1);
	}
	zx::key fromGLFWKey(int k)
	{
		size_t converted = 0;
		if (k == -1)
			converted = 0;
		else converted = static_cast<size_t>(k);
		return zx::key::Get(converted);
	}
	zx::mousebutton fromGLFWMouseButton(int b)
	{
		b += 1;
		return zx::mousebutton::Get(static_cast<size_t>(b));
	}
}