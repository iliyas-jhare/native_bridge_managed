
#include "bridge_callbacks.h"

#pragma once

struct native_calls;

using show_fn = void(*)();
using greet_fn = void(*)(const char* msg);
using create_native_calls_fn = native_calls(*)(bridge_callbacks);

struct native_calls
{
	show_fn show;
	greet_fn greet;
};

extern "C" __declspec(dllexport)
native_calls create_native_calls(bridge_callbacks callbacks);