#pragma once
#include "component.hpp"
#include "math.hpp"
#include <vector>
#include "entity.hpp"
namespace zx
{
	namespace com
	{
		struct name_tag : zxAttribute(component)
		{
			std::string name = "Entity";
			std::string tag = "none";
		};
		struct hierarchy : zxAttribute(component)
		{
			zx::entity parent; 
			std::vector<zx::entity> children;
		};
		struct transform : zxAttribute(component)
		{
			zx::matrix matrix() {
				hierarchy& h = entity->GetComponent<hierarchy>();
				if (h.parent.IsValid())
					return pm_Matrix * h.parent.GetComponent<transform>().matrix();
			}
		private:
			zx::matrix pm_Matrix;
		};
	}

}
