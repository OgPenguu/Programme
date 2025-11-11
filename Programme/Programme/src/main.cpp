#include <iostream>
#include "interface/interface.h"

int main()
{
	std::cout << "GLFW version: "
		<< GLFW_VERSION_MAJOR << "."
		<< GLFW_VERSION_MINOR << "."
		<< GLFW_VERSION_REVISION << std::endl;

	if (!interfaceNS::Initialize())
		return 1;
	interfaceNS::Render();
}