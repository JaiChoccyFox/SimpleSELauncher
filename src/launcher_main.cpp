/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#include <wx/mstream.h>
#include "launcher_main.hpp"
#include "launcher_splash.hpp"
#include "launcher_frame.hpp"

// Embedded Splash PNG
#include "res/splash.png.h"

namespace SimpleSELauncher
{
	bool MainApplication::OnInit()
	{
		// Add image handlers
		wxInitAllImageHandlers();

		// Create the main application frame
		m_pMainApplicationFrame = new MainApplicationFrame();

		// Load Splash PNG into memory
		wxMemoryInputStream splashData(SPLASH_PNG, sizeof(SPLASH_PNG));
		wxImage splashImg(splashData, wxBITMAP_TYPE_PNG);
		wxBitmap splashBmp(splashImg);

		// Create a Splash Screen
		wxSplashScreen *m_pSplashScreen = new MainSplashScreen(splashBmp);
		m_pSplashScreen->Bind(wxEVT_CLOSE_WINDOW, &MainApplication::OnSplashClose, this);
		wxYield();

		// Return!
		return true;
	}

	// Splash screen closed
	void MainApplication::OnSplashClose(wxCloseEvent& event)
	{
		// Show the main application frame
		m_pMainApplicationFrame->CentreOnScreen();
		m_pMainApplicationFrame->Show();

		// Skip the event (destroys the splash screen)
		event.Skip();
	}
}

// Initialise the main application!
wxIMPLEMENT_APP(SimpleSELauncher::MainApplication);
