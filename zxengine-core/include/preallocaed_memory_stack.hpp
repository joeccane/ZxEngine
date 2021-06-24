#pragma once
#include <utility>
#include <vector>
#include <functional>
namespace zx
{
	class iPreallocatedMemoryStack
	{
	public:
		virtual void* push(size_t size) { return nullptr; }
		virtual void pop() {}

		virtual size_t size() { return 0; }
		virtual size_t utilized() { return 0; }
	};
	namespace detail
	{
		template<size_t size>
		void initialize_allocator_stack();

		iPreallocatedMemoryStack* get_allocator_stack();

	}
	template<typename T>
	struct PreallocatedMemoryAllocator
	{
		using value_type = T;

		template<typename U> constexpr PreallocatedMemoryAllocator(const PreallocatedMemoryAllocator<U>&) noexcept {}
		PreallocatedMemoryAllocator() = default;

		[[nodiscard]] T* allocate(std::size_t n)
		{
			std::cout << "Allocate: " << n * sizeof(T) << '\n';
			auto* allocator = detail::get_allocator_stack();
			void* location = allocator->push(n * sizeof(T));
			std::memset(location, 0, n * sizeof(T));
			return (T*)location;
		}
		void deallocate(T* p, std::size_t n) noexcept
		{
			std::cout << "Deallocate : " << n * sizeof(T) << '\n';
			detail::get_allocator_stack()->pop();
		}

	};

	template<size_t size_of_blob>
	class preallocated_memory_stack : public iPreallocatedMemoryStack
	{
	public:
		bool CanAllocate(size_t size)
		{
			return (pm_Utilized + size) < size_of_blob;
		}
		void* push(size_t size)
		{
			if (!CanAllocate(size))
				return nullptr;

			void* location = static_cast<void*>(pm_Data + pm_Utilized);
			pm_Utilized += size;

			pm_DeallocStack[pm_DallocLocation] = size;
			pm_DallocLocation++;
			return location;
		}
		void pop()
		{
			if (pm_DallocLocation == 0)
				return;

			pm_DallocLocation--;
			pm_Utilized -= pm_DeallocStack[pm_DallocLocation];
		}
		size_t utilized() override { return pm_Utilized; }
		size_t size() override { return size_of_blob; }
	private:
		size_t pm_Utilized = 0;
		char pm_Data[size_of_blob];
		size_t pm_DeallocStack[size_of_blob];
		size_t pm_DallocLocation = 0;
	};
	namespace detail
	{
		template<size_t size>
		void initialize_allocator_stack()
		{
			holder<iPreallocatedMemoryStack>::value = holder<preallocated_memory_stack<size>>::value;
		}
		iPreallocatedMemoryStack* get_allocator_stack()
		{
			return holder<iPreallocatedMemoryStack>::value;
		}
	}
	
}