#pragma once
#include "vendor/entt.hpp"
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
namespace zx
{
	namespace phase
	{
#define _ZX__DefinePhaseFunc(name)\
struct name##_phase_type : entt::type_list<void()>\
{\
	template<typename Base>\
	struct type : Base\
	{\
		void name() { this->template invoke<0>(*this); }\
	};\
	template<typename Type>\
	using impl = entt::value_list<&Type::name>;\
};\
using name = entt::poly<name##_phase_type>;\
template<typename T>\
concept has_##name = requires(T t) { t.name(); }

		_ZX__DefinePhaseFunc(initialize);
		_ZX__DefinePhaseFunc(awake);
		_ZX__DefinePhaseFunc(start);

		_ZX__DefinePhaseFunc(early_update);
		_ZX__DefinePhaseFunc(update);
		_ZX__DefinePhaseFunc(late_update);

		_ZX__DefinePhaseFunc(pre_render);
		_ZX__DefinePhaseFunc(render);
		_ZX__DefinePhaseFunc(post_render);

		_ZX__DefinePhaseFunc(exit);


		template<typename FuncType>
		struct func_component
		{
			std::unordered_map<std::type_index, FuncType> map;
			template<typename T>
			void add(const FuncType func)
			{
				map.emplace(typeid(T), func);
			}
		};

#define ZX__ADDFUNC(name)\
if constexpr(has_##name<T>)\
	AddFunc<name>(id, t)
		class registry
		{
		public:
			entt::registry pm_Registry;
			template<typename FuncType, typename T>
			inline void AddFunc(entity_id id, T& t)
			{
				func_component<FuncType>* funcs = pm_Registry.try_get<func_component<FuncType>>(id);
				if (funcs == nullptr)
				{
					pm_Registry.emplace<func_component<FuncType>>(id);
					funcs = pm_Registry.try_get<func_component<FuncType>>(id);
				}

				funcs->map[typeid(T)] = FuncType{ std::reference_wrapper(t) };
			}
		public:
			inline entity_id create() { return pm_Registry.create(); }
			template<typename T>
			inline void add_functions(entity_id id, T& t)
			{
				ZX__ADDFUNC(initialize);
				ZX__ADDFUNC(awake);
				ZX__ADDFUNC(start);

				ZX__ADDFUNC(early_update);
				ZX__ADDFUNC(update);
				ZX__ADDFUNC(late_update);

				ZX__ADDFUNC(pre_render);
				ZX__ADDFUNC(render);
				ZX__ADDFUNC(post_render);

				ZX__ADDFUNC(exit);
			}
#define _ZX__PhaseCallFunc(name)\
inline void call_##name()\
{\
	auto view = pm_Registry.view<func_component<name>>();\
	for (auto v : view)\
	{\
		func_component<name>& funcs = pm_Registry.get<func_component<name>>(v);\
		for (auto& [key, value] : funcs.map)\
		{\
			value->name();\
		}\
	}\
}
			_ZX__PhaseCallFunc(initialize);
			_ZX__PhaseCallFunc(start);
			_ZX__PhaseCallFunc(awake);
			_ZX__PhaseCallFunc(early_update);
			_ZX__PhaseCallFunc(update);
			_ZX__PhaseCallFunc(late_update);

			_ZX__PhaseCallFunc(pre_render);
			_ZX__PhaseCallFunc(render);
			_ZX__PhaseCallFunc(post_render);

			_ZX__PhaseCallFunc(exit);


		};
	}
}