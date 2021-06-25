#pragma once
#include <unordered_map>
#include <stack>
#include <string_view>
namespace zx
{
	class KeyStack
	{
	public:
		void Push(std::string_view s)
		{
			if (pm_Map.contains(s.data()))
				pm_Map[s.data()]++;
			else
				pm_Map[s.data()] = 1;
		}
		void Pop(std::string_view s)
		{
			if (pm_Map.contains(s.data()))
			{
				if (pm_Map[s.data()] > 0)
					pm_Map[s.data()]--;
			}
		}
		size_t Count(std::string_view s)
		{
			if (!pm_Map.contains(s.data()))
				return 0;
			return pm_Map[s.data()];
		}
		bool Empty(std::string_view s)
		{
			if (!pm_Map.contains(s.data()))
				return true;
			return pm_Map[s.data()] == 0;
		}
	private:
		std::unordered_map<std::string, size_t> pm_Map;
	};
}