#pragma once

#include <string>

auto convert(System::String^ s)->std::string;

auto convert(std::string s)->System::String^;

auto convert(void* ptr)->System::IntPtr;
