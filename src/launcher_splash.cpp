/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#include "launcher_splash.hpp"

namespace SimpleSELauncher
{
	// Splash screen constructor
	MainSplashScreen::MainSplashScreen(const wxBitmap& bitmap)
		: wxSplashScreen(bitmap, wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_TIMEOUT, 1000, NULL, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER | wxFRAME_NO_TASKBAR | wxSTAY_ON_TOP)
	{
		// Leave this empty!
	}
}
