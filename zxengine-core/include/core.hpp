#pragma once
#include <concepts>
#include <type_traits>
#include <vendor/entt.hpp>
#include <memory_resource>
#include <memory>
#define zxIteratorFunctions(innerCollection)									\
	[[nodiscard]] auto begin() { return innerCollection.begin(); }				\
	[[nodiscard]] auto end() { return innerCollection.end(); }					\
	[[nodiscard]] auto rbegin() { return innerCollection.rbegin(); }			\
	[[nodiscard]] auto rend() { return innerCollection.rend(); }				\
	[[nodiscard]] auto cbegin() const { return innerCollection.cbegin(); }		\
	[[nodiscard]] auto cend() const { return innerCollection.cend(); }			\
	[[nodiscard]] auto crbegin() const { return innerCollection.crbegin(); }	\
	[[nodiscard]] auto crend() const { return innerCollection.crend(); }

#define zxAttribute(name) public name##_attribute
#define zxDefineAttribute(name)																\
	struct name##_attribute;																\
	template<typename T> concept name##_type = std::derived_from<T, name##_attribute>;		\
	struct name##_attribute

namespace zx
{
	template<typename T>
	using vector = std::pmr::vector<T>;

	template<typename T>
	using managed = std::shared_ptr<T>;
	template<typename T>
	using owner = std::unique_ptr<T>;

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

	
}