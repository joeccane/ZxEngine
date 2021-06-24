#pragma once
#include "core.hpp"
#include <memory_resource>
namespace zx
{
	using coms_list_memory_resource = std::pmr::synchronized_pool_resource;

	template<component_type T>
	using coms_vector = zx::vector<T>;

	struct coms_vector_resource
	{
		inline static coms_list_memory_resource resource = coms_list_memory_resource(std::pmr::pool_options{ 10, 256 });

		template<component_type T>
		inline static coms_vector<T> create()
		{
			return coms_vector<T>(&resource);
		}
	};
}