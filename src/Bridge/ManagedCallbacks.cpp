
#include "ManagedCallbacks.h"
#include "converters.h"

ManagedCallbacks::ManagedCallbacks(callbacks& callbacks)
	: cbs(callbacks)
{
}

void ManagedCallbacks::Log(System::String^ message)
{
	cbs.log(convert(message));
}

System::IntPtr ManagedCallbacks::OwnerHandle()
{
	return convert(cbs.owner_handle());
}
