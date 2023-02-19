/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#pragma once

#include <vector>
#include <boost/dll.hpp>

namespace SimpleSELauncher::utils
{
	void FindTargetExecutable(const boost::filesystem::path &directory, const boost::filesystem::path &file_name, std::vector<boost::filesystem::path> &vec);
}
