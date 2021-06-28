#pragma once
#include "vendor/entt.hpp"
#include "core.hpp"
#include <utility>
#include "gamephase.hpp"
#include "math.hpp"
#include "component.hpp"
#include "registry.hpp"
namespace zx
{
	struct entity
	{
		[[nodiscard]] inline entity() noexcept
			: pm_ID(entt::null), pm_Scene(nullptr) {}
		[[nodiscard]] inline entity(SceneRegistry* scene) 
			: pm_ID(scene->registry.create()), pm_Scene(scene) {
		}

		template<component_type T, typename... Args>
		inline T& AddComponent(Args&&...a)
		{
			pm_Scene->registry.emplace<T>(pm_ID, std::forward<Args>(a)...);
			auto& result = pm_Scene->registry.get<T>(pm_ID);
			phase::RegisterAll<T,
				phase::awake,
				phase::initialize,
				phase::start,
				phase::early_update,
				phase::update,
				phase::late_update,
				phase::pre_render,
				phase::render,
				phase::post_render,
				phase::dispose,
				phase::exit>(result, pm_Scene->sceneID);
			result.entity = this;
			return result;
		}
		template<component_type T>
		[[nodiscard]] inline T& GetComponent() {
			return pm_Scene->registry.get<T>(pm_ID);
		}
		template<component_type T>
		[[nodiscard]] inline bool HasComponent() noexcept{
			return pm_Scene->registry.try_get<T>(pm_ID) != nullptr;
		}
		[[nodiscard]] inline bool IsValid() noexcept { return pm_ID != entt::null; }

		inline size_t CountChildren(bool recursive = false)
		{
			size_t count = 0;
			count += children().size();
			if (recursive)
			{
				for (auto e : children())
					count += e.CountChildren(true);
			}
			return count;
		}
		template<component_type T>
		[[nodiscard]] inline std::vector<T> GetComponentsInChildren(bool recursive = false)
		{
			std::vector<T> coms;
			coms.reserve(CountChildren(recursive));

			for (auto& child : children())
			{
				if (child.HasComponent<T>())
				{
					coms.push_back(&child.GetComponent<T>());
					if (recursive)
					{
						auto innerComponents = child.GetComponentsInChildren<T>();
						for (auto com : innerComponents)
							coms.push_back(com);
					}
				}
			}
			return coms;
		}

		std::string_view name();
		std::string_view tag();
		zx::matrix matrix();
		std::vector<entity>& children();
		entity parent();
		void SetParent(entity e);
		void AddChild(entity e);
		void RemoveChild(entity e);

		bool operator!=(entity other) { return pm_ID != other.pm_ID; }
		bool operator==(entity other) { return pm_ID == other.pm_ID; }

	private:
		entt::entity pm_ID;
		SceneRegistry* pm_Scene;


		friend class scene;
	};
}