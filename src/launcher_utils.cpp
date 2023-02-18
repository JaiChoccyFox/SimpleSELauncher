/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#include <vector>
#include <filesystem>
#include "boost/dll.hpp"
#include "boost/algorithm/string.hpp"
#include "launcher_utils.hpp"

#if defined(__WIN32__)
#include "windows.h"
#endif

namespace filesys = std::filesystem;
namespace boostdll = boost::dll;
namespace boostutils = boost::algorithm;

namespace SimpleSELauncher::utils
{
	// Converts a "pretty" name to a file name, used to display names in the choice dialogs in-app
	std::string PrettyNameToFileName(const std::string& name)
	{
		if (name == "Mod Organiser")
			return "ModOrganiser";
		else if (name == "Mod Organizer")
			return "ModOrganizer";
		else if (name == "MSVC++ Redistributable x64")
			return "VC_redist.x64";
		else if (name == "MSVC++ Redistributable x86")
			return "VC_redist.x86";
		else if (name == "Nexus Mod Manager")
			return "NMM";
		else if (name == "SKSE64 Loader")
			return "skse64_loader";
		else if (name == "Skyrim SE")
			return "SkyrimSE";
		else if (name == "Skyrim SE Launcher")
			return "SkyrimSELauncher";
		else if (name == "Skyrim Together")
			return "SkyrimTogether";
		else if (name == "Skyrim Together (Server)")
			return "SkyrimTogetherServer";
		else
			return name;
	}

	// Give an EXE name (without the suffix) and return a path to the first file found, or return NULL if not found
	std::string FindTargetExecutable(const std::string& filename)
	{
#if defined(__WIN32__)
		// Store the file name
		std::string sFileName = filename;

		// Lower the filename
		boostutils::to_lower(sFileName);

		// Store the current working directory
		filesys::path currentWD(filesys::current_path());

		// Store the current executable path
		filesys::path currentEXE(boostdll::program_location().string());

		// Needed for the directory iterator below
		filesys::directory_options dirOptions = filesys::directory_options::follow_directory_symlink | filesys::directory_options::skip_permission_denied;

		// Range-based for loop for directory iterator
		for (const filesys::directory_entry& dirEntry : filesys::recursive_directory_iterator(currentWD, dirOptions))
		{
			// Check if the file exists, is a regular file, is not the current EXE and meets the String criteria!
			if (dirEntry.exists() && dirEntry.is_regular_file() && dirEntry.path().filename().string() != currentEXE.filename().string()
				&& boostutils::starts_with(boostutils::to_lower_copy(dirEntry.path().filename().string()), sFileName)
				&& boostutils::starts_with(boostutils::to_lower_copy(dirEntry.path().extension().string()), ".exe"))
				return std::filesystem::canonical(dirEntry.path()).string();
		}
#endif
		// Return an empty string upon not finding the executable (or we are not using Windows for some reason)
		return "";
	}

	// Execute a program and continue running, or stop and wait for the process to die
	bool ExecuteProgram(const std::wstring& program, const std::wstring& args, const std::wstring& dir, bool wait)
	{
		wchar_t* wcProgram = (wchar_t*)program.c_str();
		wchar_t* wcArgs = (wchar_t*)args.c_str();
		wchar_t* wcDir = (wchar_t*)dir.c_str();
		filesys::path pCDir(filesys::current_path());
		bool bWait = wait;
#if defined(__WIN32__)
		// Variables that hold information in relation to the created Process
		STARTUPINFOW si;
		PROCESS_INFORMATION pi;

		// Allocate memory for Process startup information
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);

		// Allocate memory for Process information
		ZeroMemory(&pi, sizeof(pi));

		// Create the Process if possible
		filesys::current_path(wcDir);
		DWORD dwCreationFlags = bWait ? 0 : CREATE_NEW_PROCESS_GROUP;
		if (CreateProcessW(wcProgram, wcArgs, NULL, NULL, FALSE, dwCreationFlags, NULL, wcDir, &si, &pi))
		{
			// Wait for Process to close before we continue
			if (bWait)
				WaitForSingleObject(pi.hProcess, INFINITE);

			// Be a good program, let us close the handles
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);

			filesys::current_path(pCDir);
			return true;
		}
#endif
		filesys::current_path(pCDir);
		return false;
	}
}
