#pragma once
#include "vendor/entt.hpp"
#include "entity.hpp"
#include "component.hpp"
#include "component_types.hpp"
#include "gamephase.hpp"
#include "behaviour.hpp"
#include "system.hpp"
namespace zx
{
	class scene : public LayerSystem<iSystem>
	{
	public:
		scene() : pm_Registry(), pm_PhaseRegistry() {
			pm_Registry.phaseRegistry = &pm_PhaseRegistry;
		}
		[[nodiscard]] inline entity CreateEntity()
		{
			entity result(&pm_Registry, pm_Registry.registry.create(), pm_PhaseRegistry.create());
			result.AddComponent<com::name_tag>();
			result.AddComponent<com::transform>();
			result.AddComponent<com::hierarchy>();
			return result;
		}

		template<typename Behaviour>
		void RegisterBehaviour()
		{
			pm_BehaviourInvoke[typeid(Behaviour)] = Behaviour::GetFunction(pm_Registry.registry, behaviours<Behaviour>::value);
		}

		void RunBehaviours()
		{
			for (auto& [key, value] : pm_BehaviourInvoke)
				value();
		}
		void initialize() override
		{
			LayerSystem<iSystem>::initialize();
			pm_PhaseRegistry.call_initialize();
		}
		void awake() override
		{
			LayerSystem<iSystem>::awake();
			pm_PhaseRegistry.call_awake();
		}
		void start() override
		{
			LayerSystem<iSystem>::start();
			pm_PhaseRegistry.call_start();
		}
		void early_update() override
		{
			LayerSystem<iSystem>::early_update();
			pm_PhaseRegistry.call_early_update();
		}
		void update() override
		{
			LayerSystem<iSystem>::update();
			pm_PhaseRegistry.call_update();
			RunBehaviours();
		}
		void late_update() override
		{
			LayerSystem<iSystem>::late_update();
			pm_PhaseRegistry.call_late_update();
		}
		void pre_render() override
		{
			LayerSystem<iSystem>::pre_render();
			pm_PhaseRegistry.call_pre_render();
		}
		void render() override
		{
			LayerSystem<iSystem>::render();
			pm_PhaseRegistry.call_render();
		}
		void post_render() override
		{
			LayerSystem<iSystem>::post_render();
			pm_PhaseRegistry.call_post_render();
		}

		void exit() override
		{
			LayerSystem<iSystem>::exit();
			pm_PhaseRegistry.call_exit();
		}
	private:
		friend struct entity;

		detail::scene_reg pm_Registry;
		phase::registry pm_PhaseRegistry;
		std::unordered_map<std::type_index, std::function<void()>> pm_BehaviourInvoke;

		template<typename BehaviourType>
		struct behaviours
		{
			inline static BehaviourType value;
		};
	};
}