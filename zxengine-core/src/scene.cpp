#include "pch.hpp"

#include "scene/scene.hpp"

namespace zx
{
	entity scene::CreateEntity() noexcept
	{
		entity result(&pm_Registry, pm_Registry.registry.create(), pm_PhaseRegistry.create());
		result.AddComponent<com::name_tag>();
		result.AddComponent<com::transform>();
		result.AddComponent<com::hierarchy>();
		return result;
	}

	void scene::initialize()
	{
		LayerSystem<iSystem>::initialize();
		pm_PhaseRegistry.call_initialize();
	}
	void scene::awake()
	{
		LayerSystem<iSystem>::awake();
		pm_PhaseRegistry.call_awake();
	}
	void scene::start()
	{
		LayerSystem<iSystem>::start();
		pm_PhaseRegistry.call_start();
	}
	void scene::early_update()
	{
		LayerSystem<iSystem>::early_update();
		pm_PhaseRegistry.call_early_update();
	}
	void scene::update()
	{
		LayerSystem<iSystem>::update();
		pm_PhaseRegistry.call_update();
		RunBehaviours();
	}
	void scene::late_update()
	{
		LayerSystem<iSystem>::late_update();
		pm_PhaseRegistry.call_late_update();
	}
	void scene::pre_render()
	{
		LayerSystem<iSystem>::pre_render();
		pm_PhaseRegistry.call_pre_render();
	}
	void scene::render()
	{
		LayerSystem<iSystem>::render();
		pm_PhaseRegistry.call_render();
	}
	void scene::post_render()
	{
		LayerSystem<iSystem>::post_render();
		pm_PhaseRegistry.call_post_render();
	}

	void scene::exit()
	{
		LayerSystem<iSystem>::exit();
		pm_PhaseRegistry.call_exit();
	}
}