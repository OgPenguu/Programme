#ifndef INTERFACE_H
#define INTERFACE_H

#include "imgui/imgui.h"
#include "variables.h"

namespace interfaceNS
{
	void Styles();
	void Render();
	bool RenderInterface();

	bool Initialize();
	void Shutdown();
}

#endif // INTERFACE_H