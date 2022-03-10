
#include "native_calls.h"

#include <Windows.h>
#include <Shlwapi.h>
#include <memory>
#include <filesystem>
#include <istream>
#include <iostream>
#include <string>

namespace
{
	constexpr const char* bridge_dll = "Bridge.dll";

	auto load_module(const wchar_t* name) -> HMODULE
	{
		return LoadLibraryW(name);
	}

	auto free_module(HMODULE module) -> BOOL
	{
		return FreeLibrary(module);
	}

	auto get_proc_address(HMODULE module, LPCSTR name) -> FARPROC
	{
		return GetProcAddress(module, name);
	}

	auto get_module_dir() -> std::wstring
	{
		WCHAR path[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, path, MAX_PATH);
		PathRemoveFileSpec(path);
		return std::wstring{ path };
	}

	auto get_file_path(const char* name) -> std::wstring
	{
		auto dir = get_module_dir();
		std::filesystem::path path{ dir };
		path = path / name;
		return path.wstring();
	}

	void log(const char* msg)
	{
		std::cout << msg << std::endl;
	}

	void* owner_handle()
	{
		return GetConsoleWindow();
	}

	auto create_bridge_callbacks() -> bridge_callbacks
	{
		return { log, owner_handle };
	}
}

class module
{
public:
	explicit module(const std::wstring name)
		: handle(load_module(name.c_str()))
	{
	}

	~module()
	{
		free_module(handle);
	}

	template<typename T>
	T get_procedure(LPCSTR name)
	{
		return T(get_proc_address(handle, name));
	}

private:
	HMODULE handle;
};

int main()
{
	auto mdl = std::make_shared<module>(get_file_path(bridge_dll));
	native_calls calls;
	try
	{
		const auto func_name = "create_native_calls";
		const auto proc = mdl->get_procedure<create_native_calls_fn>(func_name);
		calls = proc(create_bridge_callbacks());
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return 0;
	}

	std::cout
		<< "Please enter command:" << std::endl
		<< "  show   -  to show window" << std::endl
		<< "  exit   -  to exit application" << std::endl
		<< "  greet  -  send greetings to managed" << std::endl
		<< "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;

	auto keep = true;
	do
	{
		std::string line;
		if (std::getline(std::cin, line))
		{
			keep = line != "exit";
			if (line == "show")
			{
				calls.show();
			}
			if (line == "greet")
			{
				calls.greet("Greetings from Native");
			}
		}
	} while (keep);
}
