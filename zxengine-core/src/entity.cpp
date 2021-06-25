#include "pch.hpp"
#include "scene/ecs.hpp"
#include <string_view>
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