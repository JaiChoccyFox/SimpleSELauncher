/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#pragma once

#include <string>

namespace SimpleSELauncher::utils
{
	std::string PrettyNameToFileName(const std::string& name);
	std::string FindTargetExecutable(const std::string& filename);

	bool ExecuteProgram(const std::wstring& program, const std::wstring& args, const std::wstring& dir, bool wait);
}
