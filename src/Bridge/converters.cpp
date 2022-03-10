
#include "converters.h"

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>
#include <msclr/marshal_windows.h>

auto convert(System::String^ s)->std::string
{
	return msclr::interop::marshal_as<std::string>(s);
}

auto convert(std::string s)->System::String^
{
	return msclr::interop::marshal_as<System::String^>(s);
}