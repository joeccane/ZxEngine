#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <concepts>
#include "scene/ecs.hpp"
#include "time.hpp"
#include "system.hpp"
namespace zx
{
	class application : public LayerSystem<iSystem>
	{
	public:

		[[nodiscard]] const std::string_view name() const noexcept { return pm_Name; }
		std::string& name() { return pm_Name; }


		template<std::derived_from<scene> T>
		T* CreateScene(std::string_view name)
		{
			T* result = new T();
			pm_Scenes[name.data()] = result;
			return result;
		}
#define ZX__CallSceneFunc(name)\
for(auto& [key, value] : pm_Scenes)\
	value->name();
		void Run()
		{
			
			pm_Running = true;
			initialize();
			ZX__CallSceneFunc(initialize);

			awake();
			ZX__CallSceneFunc(awake);

			start();
			ZX__CallSceneFunc(start);

			while (pm_Running)
			{
				zx::time::update();

				early_update();
				ZX__CallSceneFunc(early_update);

				update();
				ZX__CallSceneFunc(update);

				late_update();
				ZX__CallSceneFunc(late_update);



				pre_render();
				ZX__CallSceneFunc(pre_render);

				render();
				ZX__CallSceneFunc(render);

				post_render();
				ZX__CallSceneFunc(post_render);
			}

			exit();
			ZX__CallSceneFunc(exit);
		}
		void ExitApplication()
		{
			pm_Running = false;
		}
	private:
		std::unordered_map<std::string, scene*> pm_Scenes;
		bool pm_Running = false;
		std::string pm_Name = "zxengine Application";

	};
}