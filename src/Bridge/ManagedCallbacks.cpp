
#include "ManagedCallbacks.h"
#include "converters.h"

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal_windows.h>

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
	return msclr::interop::marshal_as<System::IntPtr>(cbs.owner_handle());
}
