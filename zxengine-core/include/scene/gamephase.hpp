#pragma once
#include "vendor/entt.hpp"
#include <typeindex>
#include <typeinfo>
#include <set>
#include "component.hpp"

#define _ZX_DEFINE_PHASE(NAME)\
	template<typename T>\
	concept has_##NAME = zx::component_type<T> && requires(T t) {	\
		{ t.NAME() } -> std::same_as<void>;						\
	};																\
	struct NAME : zxAttribute(phase)								\
	{																\
		template<zx::component_type T>								\
			inline static constexpr bool has = has_##NAME<T>;		\
																	\
		template<zx::component_type T>								\
		inline static void Call(T * v) {							\
			v->NAME();												\
		}															\
	}
namespace zx
{
	class scene;

	namespace phase
	{
		
		zxDefineAttribute(phase) {};

		namespace detail
		{
			template<phase_type Phase, component_type T>
			struct zx_reg 
			{
				inline static std::vector<T*> values;
			};
		}

		template<phase_type T>
		struct call_phase
		{
			using component_function_map = std::unordered_map<std::type_index, std::function<void()>>;

			inline static std::unordered_map<size_t, component_function_map> functions;
		};
		_ZX_DEFINE_PHASE(awake);
		_ZX_DEFINE_PHASE(initialize);
		_ZX_DEFINE_PHASE(start);

		_ZX_DEFINE_PHASE(early_update);
		_ZX_DEFINE_PHASE(update);
		_ZX_DEFINE_PHASE(late_update);

		_ZX_DEFINE_PHASE(pre_render);
		_ZX_DEFINE_PHASE(render);
		_ZX_DEFINE_PHASE(post_render);

		_ZX_DEFINE_PHASE(exit);
		_ZX_DEFINE_PHASE(dispose);

		template<component_type T, phase_type Phase>
		inline void Register(T& t, size_t id)
		{
			if constexpr (Phase::template has<T>) {

				detail::zx_reg<Phase, T>::values.push_back(&t);

				if (!call_phase<Phase>::functions[id].contains(typeid(Phase))) {
					call_phase<Phase>::functions[id][typeid(Phase)] = [=]() {
						for (auto v : detail::zx_reg<Phase, T>::values)
							Phase::template Call<T>(v);
					};
				}
			}
		}
		template<component_type T, phase_type Phase>
		inline void Register(T* t, size_t id)
		{
			Register<T, Phase>(*t, id);
		}
		template<component_type T, phase_type ...Phases>
		void RegisterAll(T& t, size_t id)
		{
			(Register<T, Phases>(t, id), ...);
		}
		template<component_type T, phase_type ...Phases>
		void RegisterAll(T* t, size_t id)
		{
			(Register<T, Phases>(t, id), ...);
		}
		template<phase_type Phase>
		inline void Call(size_t id)
		{
			for (auto& [key, functions] : call_phase<Phase>::functions[id])
				functions();
		}
	}
}