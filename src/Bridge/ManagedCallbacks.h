
#include "callbacks.h"

#pragma once

public ref class ManagedCallbacks : public Managed::IManagedCallbacks
{
public:
	explicit ManagedCallbacks(callbacks& callbacks);
	virtual void Log(System::String^ message);
	virtual System::IntPtr OwnerHandle();
private:
	callbacks& cbs;
};
