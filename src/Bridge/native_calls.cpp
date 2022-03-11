
#include "native_calls.h"
#include "callbacks.h"
#include "ManagedCallbacks.h"
#include "converters.h"

#include <exception>

namespace
{
	callbacks_ptr callbacks_p;

	void log(const char* msg)
	{
		if (callbacks_p)
		{
			callbacks_p->log(msg);
		}
	}

	void show()
	{
		try
		{
			Managed::ManagedBridge::Show(gcnew ManagedCallbacks(*callbacks_p));
		}
		catch (const std::exception& e)
		{
			log(e.what());
		}
	}

	void greet(const char* msg)
	{
		try
		{
			Managed::ManagedBridge::Greet(convert(msg));
		}
		catch (const std::exception& e)
		{
			log(e.what());
		}
	}
}

native_calls create_native_calls(bridge_callbacks b_callbacks)
{
	try
	{
		callbacks_p = callbacks::create(b_callbacks);
		return { show, greet };
	}
	catch (const std::exception& e)
	{
		log(e.what());
		return {};
	}
}