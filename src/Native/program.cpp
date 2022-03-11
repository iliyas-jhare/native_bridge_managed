
#include "native_calls.h"
#include "file_system.h"
#include "callbacks.h"

#include <cassert>
#include <Windows.h>
#include <memory>
#include <istream>
#include <iostream>

namespace
{
	constexpr const char* bridge_dll = "Bridge.dll";
	constexpr const char* create_native_calls_func_name = "create_native_calls";

	class module
	{
	public:
		explicit module(const wchar_t* name)
			: file_name(name)
			, h_module(LoadLibraryW(name))
		{}

		~module()
		{
			assert(FreeLibrary(h_module));
		}

		template<typename T>
		T get_proc_address(const char* name)
		{
			return T(GetProcAddress(h_module, name));
		}

	private:
		std::wstring file_name;
		HMODULE h_module;
	};

	auto load_bridge_module() -> std::shared_ptr<module>
	{
		return std::make_shared<module>(get_file_path(bridge_dll).c_str());
	}

	auto create_native_calls(std::shared_ptr<module> module_p) -> native_calls
	{
		const auto proc = module_p->get_proc_address<create_native_calls_fn>(create_native_calls_func_name);
		assert(proc);
		return proc(create_bridge_callbacks());
	}

	void show_program_help()
	{
		std::cout
			<< "Please enter command:" << std::endl
			<< "  show   -  to show window" << std::endl
			<< "  exit   -  to exit application" << std::endl
			<< "  greet  -  send greetings to managed" << std::endl
			<< "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl;
	}

	void handle_commands(const native_calls& calls)
	{
		auto keep = true;
		while (keep)
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
		}
	}
}

int main()
{
	try
	{
		std::shared_ptr<module> module_p = load_bridge_module();
		assert(module_p);
		native_calls calls = create_native_calls(module_p);
		assert(calls);
		show_program_help();
		handle_commands(calls);
		return 1;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return 0;
	}
}
