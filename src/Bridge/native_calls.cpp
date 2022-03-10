
#include "native_calls.h"
#include "callbacks.h"
#include "ManagedCallbacks.h"
#include "converters.h"

#include <exception>

namespace
{
	using namespace System;
	using namespace Threading;

	callbacks_ptr callbacks_p;

	ref class clr_calls abstract sealed
	{
	public:
		static void show()
		{
			Managed::ManagedBridge::Show(gcnew ManagedCallbacks(*callbacks_p));
		}

		static void greet(std::string s)
		{
			Managed::ManagedBridge::Greet(convert(s));
		}
	};

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
			Thread^ thread = gcnew Thread(gcnew ThreadStart(&clr_calls::show));
			thread->SetApartmentState(ApartmentState::STA);
			thread->Start();
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
			clr_calls::greet(msg);
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