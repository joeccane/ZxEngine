#pragma once
#include "vendor/entt.hpp"
#include "core.hpp"
#include <utility>
#include "gamephase.hpp"
#include "scene/coms_vector.hpp"
namespace zx
{
	namespace detail
	{
		struct scene_reg
		{
			entt::registry registry;
			phase::registry* phaseRegistry = nullptr;
		};
	}
	struct entity
	{
		inline entity() noexcept
			: pm_ID(entt::null), pm_PhaseID(entt::null), pm_SceneReg(nullptr) {}
		
		[[nodiscard]] inline entity(detail::scene_reg* sceneReg, entt::entity id, entt::entity phaseID) noexcept
			: pm_ID(id), pm_PhaseID(phaseID), pm_SceneReg(sceneReg) {}
		template<component_type T, typename... Args>
		inline T& AddComponent(Args&&...a)
		{
			pm_SceneReg->registry.emplace<T>(pm_ID, std::forward<Args>(a)...);
			auto& result = pm_SceneReg->registry.get<T>(pm_ID);
			result.entity = *this;
			pm_SceneReg->phaseRegistry->add_functions(pm_PhaseID, result);
			return result;
		}
		template<component_type T>
		[[nodiscard]] inline T& GetComponent()
		{
			return pm_SceneReg->registry.get<T>(pm_ID);
		}

		template<component_type T>
		[[nodiscard]] bool HasComponent() noexcept
		{
			return pm_SceneReg->registry.try_get<T>(pm_ID) != nullptr;
		}
		[[nodiscard]] inline bool IsValid() noexcept { return pm_ID != entt::null && pm_PhaseID != entt::null; }

		size_t CountChildren(bool recursive = false)
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
		[[nodiscard]] coms_vector<T> GetComponentsInChildren(bool recursive = false)
		{
			coms_vector<T> coms = coms_vector_resource::create<T>();
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
		entt::entity pm_PhaseID;

		friend class scene;
		detail::scene_reg* pm_SceneReg;
	};
}