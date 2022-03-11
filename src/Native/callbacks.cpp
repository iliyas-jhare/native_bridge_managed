
#include "callbacks.h"

#include <Windows.h>
#include <iostream>

namespace
{
	void log(const char* msg)
	{
		std::cout << msg << std::endl;
	}

	void* owner_handle()
	{
		return GetConsoleWindow();
	}
}

auto create_bridge_callbacks()->bridge_callbacks
{
	return { log, owner_handle };
}