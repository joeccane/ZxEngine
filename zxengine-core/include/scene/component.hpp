#pragma once
#include "core.hpp"

namespace zx
{
	struct entity;
	zxDefineAttribute(component) {
		entity* entity;
	};
}