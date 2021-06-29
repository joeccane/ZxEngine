#pragma once
#include "core.hpp"
#include "ecs.hpp"
#include <functional>
namespace zx
{

	zxDefineAttribute(optimize_behaviour);

	template<typename Parent, component_type ...Coms>
	class behaviour
	{
	public:
		virtual void run(Coms&...a) = 0;
		using behaviour_type = behaviour;

	private:
		friend class scene;

		inline static std::function<void()> GetFunction(entt::registry& reg, Parent& parent)
		{
			return [&]()
			{
				if constexpr (optimize_behaviour_type<Parent>)
				{
					auto group = reg.group<>(entt::get<Coms...>);
					for (auto e : group)
					{
						parent.run(group.get<Coms>(e)...);
					}
				}
				else
				{
					reg.view<Coms...>().each([&](entt::entity entity, Coms&...coms) {
						parent.run(coms...);
					});
				}
			};
		}
	};
}
