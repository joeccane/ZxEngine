#pragma once
#include "core.hpp"
#include <concepts>
#include <queue>
#include "math.hpp"
namespace zx
{
	template<std::integral T>
	class id_counter
	{
	public:
		[[nodiscard]] constexpr T get() noexcept
		{
			if (pm_ReturnedIds.size() > 0)
			{
				T result = pm_ReturnedIds.front();
				pm_ReturnedIds.pop();
				return result;
			}
			else return pm_Count++;
		}

		[[nodiscard]] constexpr unsigned long long int count() noexcept
		{
			return static_cast<unsigned long long int>(-(math::min<T>() - pm_Count) - pm_ReturnedIds.size());
		}
		[[nodiscard]] constexpr void ret(T id) noexcept {
			pm_ReturnedIds.push(id);
		}
	private:
		T pm_Count;
		std::queue<T> pm_ReturnedIds;
	};
}