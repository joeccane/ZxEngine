#pragma once
#include <concepts>

#include "core.hpp"
#include "entity.hpp"

namespace zx
{
	struct component 
	{
		zx::entity entity;
	};
}