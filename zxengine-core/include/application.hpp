#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <concepts>

#include "scene/ecs.hpp"
#include "time.hpp"
#include "system.hpp"
#include "KeyStack.hpp"
#include "window.hpp"
namespace zx
{
	class application : public LayerSystem<iSystem>
	{
	public:

		[[nodiscard]] const std::string_view name() const noexcept { return pm_Name; }
		std::string& name() { return pm_Name; }


		template<std::derived_from<scene> T>
		[[nodiscard]] T* CreateScene(std::string_view name) noexcept
		{
			T* result = new T();
			pm_Scenes[name.data()] = result;
			return result;
		}
		template<std::derived_from<window> T>
		[[nodiscard]] managed<T> CreateWindow(const WindowOptions& options = WindowOptions())
		{
			managed<T> result(new T());

			const T* cResult = static_cast<const T*>(result.get());
			auto _discard1 = result->onSystemInit << [&, result, cResult](SystemConstructEventData& data)
			{
				if (pm_KeyStack.Empty(cResult->stackKey()))
					result->NativeInitialization();
				pm_KeyStack.Push(cResult->stackKey());
				if (data.appBlocking)
					pm_KeyStack.Push(appBlockStackKey);
			};

			auto _discard2 = result->onSystemDispose << [&, result, cResult](SystemConstructEventData& data)
			{
				pm_KeyStack.Pop(data.stackKey);
				if (pm_KeyStack.Empty(data.stackKey))
					result->NativeDispose();
				if (data.appBlocking)
					pm_KeyStack.Pop(appBlockStackKey);
			};
			Add(result.get());
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

				for (auto& [key, value] : pm_Scenes)
					value->LocalTimeUpdate();
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


				if (pm_KeyStack.Count(appBlockStackKey) == 0)
					pm_Running = false;
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

		std::string pm_Name = "zxengine Application";
		KeyStack pm_KeyStack;
		bool pm_Running = false;

		inline static const std::string appBlockStackKey = "__zxengine app block";

	};
}