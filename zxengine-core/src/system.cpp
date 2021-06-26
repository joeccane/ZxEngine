#include "pch.hpp"
#include "system.hpp"

namespace zx
{
	void iSystem::LayerAdded()
	{
		SystemConstructEventData ed;
		ed.appBlocking = pm_ApplicationBlocking;
		ed.handled = false;
		ed.stackKey = pm_StackKey;

		onSystemInit.Invoke(ed);
	}
	void iSystem::LayerRemoved()
	{
		SystemConstructEventData ed;
		ed.appBlocking = pm_ApplicationBlocking;
		ed.handled = false;
		ed.stackKey = pm_StackKey;

		onSystemDispose.Invoke(ed);
	}

}