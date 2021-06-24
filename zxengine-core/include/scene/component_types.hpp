#pragma once
#include "component.hpp"
#include "math.hpp"
#include <vector>
#include "entity.hpp"
namespace zx
{
	namespace com
	{
		struct name_tag : public component
		{
			std::string name = "Entity";
			std::string tag = "none";
		};
		struct hierarchy : public component
		{
			zx::entity parent; 
			std::vector<zx::entity> children;
		};
		struct transform : public component
		{
			zx::matrix matrix() {
				hierarchy& h = entity.GetComponent<hierarchy>();
				if (h.parent.IsValid())
					return pm_Matrix * h.parent.GetComponent<transform>().matrix();
			}
		private:
			zx::matrix pm_Matrix;
		};
	}

}
inline std::string_view zx::entity::name()
{
	return GetComponent<zx::com::name_tag>().name;
}
inline std::string_view zx::entity::tag()
{
	return GetComponent<zx::com::name_tag>().tag;
}
inline zx::matrix zx::entity::matrix()
{
	return GetComponent<zx::com::transform>().matrix();
}

inline std::vector<zx::entity>& zx::entity::children()
{
	return GetComponent<zx::com::hierarchy>().children;
}

inline zx::entity zx::entity::parent()
{
	return GetComponent<zx::com::hierarchy>().parent;
}

void zx::entity::SetParent(entity e)
{
	if (!e.HasComponent<com::hierarchy>())
		assert(false);

	GetComponent<com::hierarchy>().parent = e;
}
void zx::entity::AddChild(entity e)
{
	if (!e.HasComponent<com::hierarchy>())
		assert(false);

	GetComponent<com::hierarchy>().children.push_back(e);
}
void zx::entity::RemoveChild(entity e)
{
	if (!e.HasComponent<com::hierarchy>())
		assert(false);
	std::vector<entity>& children = GetComponent<com::hierarchy>().children;

	auto result = std::find(begin(children), end(children), e);
	if (result != end(children))
		children.erase(result);
}