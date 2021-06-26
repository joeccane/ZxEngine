#pragma once
#include <type_traits>
#include <vendor/entt.hpp>
#include <memory_resource>
#define zxIteratorFunctions(innerCollection)\
	[[nodiscard]] auto begin() { return innerCollection.begin(); }\
	[[nodiscard]] auto end() { return innerCollection.end(); }\
	[[nodiscard]] auto rbegin() { return innerCollection.rbegin(); }\
	[[nodiscard]] auto rend() { return innerCollection.rend(); }\
	[[nodiscard]] auto cbegin() const { return innerCollection.cbegin(); }\
	[[nodiscard]] auto cend() const { return innerCollection.cend(); }\
	[[nodiscard]] auto crbegin() const { return innerCollection.crbegin(); }\
	[[nodiscard]] auto crend() const { return innerCollection.crend(); }

namespace zx
{
	template<typename T>
	using vector = std::pmr::vector<T>;


	namespace detail
	{
		template<typename CheckedType, typename T1, typename ...ANY>
		struct is_one_of_detail
		{
			const bool value = std::is_same_v<CheckedType, T1> && is_one_of_detail<CheckedType, ANY...>::value;
		};
		template<typename CheckedType, typename T1>
		struct is_one_of_detail<CheckedType, T1>
		{
			const bool value = std::is_same_v<CheckedType, T1>;
		};
	}
	template<typename T, typename ...ANY>
	concept is_one_of = detail::is_one_of_detail<T, ANY...>::value;


	template<typename T, size_t id = 0>
	struct holder
	{
		inline static T* value = new T();
	};


	using entity_id = entt::entity;


	template<typename T>
	struct ref_wrapper
	{
		using wrapped = T;
		T* value;
		ref_wrapper() = default;
		ref_wrapper(T& value) : value(&value) {}
		ref_wrapper(const ref_wrapper& copy) : value(copy.value) {}
		T* operator->() { return value; }
		ref_wrapper& operator=(const ref_wrapper& other){
			value = other.value;
			return *this;
		}
	};

	struct component;


	template<typename T>
	concept component_type = std::derived_from<T, component>;

	template<component_type T>
	struct com_ref
	{
		com_ref() = default;
		com_ref(const com_ref& copy) = default;
		com_ref(com_ref&& move) = default;

		inline com_ref(T& com, entity_id parent) : parent(parent), pm_Value(&com) {}
		entity_id parent;
		T& value() { return *pm_Value; }
		T* operator-> () { return pm_Value; }
	private:
		T* pm_Value;
	};



	
}