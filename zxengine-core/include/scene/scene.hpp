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
		[[nodiscard]] inline entity CreateEntity() noexcept;

		template<typename Behaviour>
		inline void RegisterBehaviour() noexcept {
			pm_BehaviourInvoke[typeid(Behaviour)] = Behaviour::GetFunction(pm_Registry.registry, behaviours<Behaviour>::value);
		}

		inline void RunBehaviours() {
			for (auto& [key, value] : pm_BehaviourInvoke)
				value();
		}
		void initialize() override;
		void awake() override;
		void start() override;

		void early_update();
		void update() override;
		void late_update();

		void pre_render() override;
		void render() override;
		void post_render() override;

		void exit() override;

	private:

		detail::scene_reg pm_Registry;
		phase::registry pm_PhaseRegistry;

		std::unordered_map<std::type_index, std::function<void()>> pm_BehaviourInvoke;

		template<typename BehaviourType>
		struct behaviours
		{
			inline static BehaviourType value;
		};


		friend struct entity;
	};
}