
#include "file_system.h"

#include <Shlwapi.h>
#include <filesystem>

auto get_program_dir() -> std::wstring
{
	WCHAR path[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, path, MAX_PATH);
	PathRemoveFileSpec(path);
	return std::wstring{ path };
}

auto get_file_path(const char* name) -> std::wstring
{
	auto dir = get_program_dir();
	std::filesystem::path path{ dir };
	path = path / name;
	return path.wstring();
}