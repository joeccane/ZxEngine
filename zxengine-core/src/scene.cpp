#include "pch.hpp"

#include "scene/scene.hpp"

namespace zx
{
	entity scene::CreateEntity() noexcept
	{
		entity result(&pm_Registry);
		result.AddComponent<com::name_tag>();
		result.AddComponent<com::transform>();
		result.AddComponent<com::hierarchy>();
		return result;
	}

	void scene::initialize()
	{
		LayerSystem<iSystem>::initialize();
		phase::Call<phase::initialize>(id());
	}
	void scene::awake()
	{
		LayerSystem<iSystem>::awake();
		phase::Call<phase::awake>(id());
	}
	void scene::start()
	{
		LayerSystem<iSystem>::start();
		phase::Call<phase::start>(id());
	}
	void scene::early_update()
	{
		LayerSystem<iSystem>::early_update();
		phase::Call<phase::early_update>(id());
	}
	void scene::update()
	{
		LayerSystem<iSystem>::update();
		phase::Call<phase::update>(id());
		RunBehaviours();
	}
	void scene::late_update()
	{
		LayerSystem<iSystem>::late_update();
		phase::Call<phase::late_update>(id());
	}
	void scene::pre_render()
	{
		LayerSystem<iSystem>::pre_render();
		phase::Call<phase::pre_render>(id());
	}
	void scene::render()
	{
		LayerSystem<iSystem>::render();
		phase::Call<phase::render>(id());
	}
	void scene::post_render()
	{
		LayerSystem<iSystem>::post_render();
		phase::Call<phase::post_render>(id());
	}

	void scene::exit()
	{
		LayerSystem<iSystem>::exit();
		phase::Call<phase::exit>(id());
	}
}