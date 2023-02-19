/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#include <string>
#include <boost/algorithm/string.hpp>
#include "launcher_utils.hpp"

namespace algorithm = boost::algorithm;
namespace dll = boost::dll;
namespace filesystem = boost::filesystem;
using std::wstring;
using std::vector;
using dll::program_location;
using filesystem::path;
using filesystem::recursive_directory_iterator;
using filesystem::directory_entry;

namespace SimpleSELauncher::utils
{
	// Recursively search through the given directory for a specified file name, storing it back into a given vector
	void FindTargetExecutable(const path &directory, const path &file_name, vector<path> &vec)
	{
		// Recursive directory iterators search through all directories under the given directory for a specific file name
		recursive_directory_iterator directoryIter(directory);
		std::copy_if(directoryIter, filesystem::end(directoryIter), std::back_inserter(vec), [&file_name](const directory_entry &directoryEntry)
		{
#if defined(__WIN32__)
			wstring fileNamePath = directoryEntry.path().filename().native();
			return directoryEntry.path() != program_location()
					&& algorithm::icontains(fileNamePath, file_name.native()) && algorithm::icontains(fileNamePath, L".exe");
#else
			return directoryEntry.path() != program_location()
					&& algorithm::icontains(directoryEntry.path().filename().native(), file_name.native());
#endif
		});
	}
}
