#pragma once
#include <vendor/entt.hpp>

namespace zx
{
	struct SceneRegistry 
	{
		SceneRegistry(size_t& sceneID) 
			: sceneID(sceneID), registry() {}
		entt::registry registry;
		size_t& sceneID;
	};
}