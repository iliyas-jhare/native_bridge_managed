#pragma once

struct bridge_callbacks;

using handle_t = void*;
using log_fn = void(*)(const char* msg);
using owner_handle_fn = void* (*)();

struct bridge_callbacks
{
	log_fn log;
	owner_handle_fn owner_handle;
};
