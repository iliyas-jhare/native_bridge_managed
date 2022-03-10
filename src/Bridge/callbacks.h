
#include <bridge_callbacks.h>
#include <memory>
#include <string>

#pragma once

typedef std::shared_ptr<struct callbacks> callbacks_ptr;

struct callbacks
{
	static callbacks_ptr create(bridge_callbacks callbacks);
	virtual ~callbacks() = default;
	virtual void log(const std::string& msg) const = 0;
	virtual void* owner_handle() const = 0;
};
