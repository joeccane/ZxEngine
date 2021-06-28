#pragma once
#include "vendor/entt.hpp"
#include "entity.hpp"
#include "component.hpp"
#include "component_types.hpp"
#include "gamephase.hpp"
#include "behaviour.hpp"
#include "system.hpp"
#include "registry.hpp"
namespace zx
{
	class scene : public LayerSystem<iSystem>
	{
	public:
		scene() : pm_Registry(pm_ID), pm_BehaviourInvoke(), pm_ID(ps_Counter.get()) {
		}

		[[nodiscard]] entity CreateEntity() noexcept;

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
		inline size_t id() const { return pm_ID; }
	private:


		std::unordered_map<std::type_index, std::function<void()>> pm_BehaviourInvoke;
		SceneRegistry pm_Registry;
		template<typename BehaviourType>
		struct behaviours
		{
			inline static BehaviourType value;
		};

		inline static id_counter<size_t> ps_Counter;
		size_t pm_ID;
		friend struct entity;
	};
}