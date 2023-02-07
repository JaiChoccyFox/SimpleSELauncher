/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#include "wx/mstream.h"
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
		m_pMainApplicationFrame->CentreOnScreen();

		// Fix the position of the Launcher frame, because for some reason it does not centre properly?
		wxPoint framePos = m_pMainApplicationFrame->GetPosition();
		wxSize frameSize = m_pMainApplicationFrame->GetSize();
		m_pMainApplicationFrame->SetPosition(wxPoint(framePos.x - frameSize.x / 2, framePos.y - frameSize.y / 2));

		// Load Splash PNG into memory
		wxMemoryInputStream splashData(SPLASH_PNG, sizeof(SPLASH_PNG));
		wxImage splashImg(splashData, wxBITMAP_TYPE_PNG);
		wxBitmap splashBmp(splashImg);

		// Create a Splash Screen
		wxSplashScreen* m_pSplashScreen = new MainSplashScreen(splashBmp);
		m_pSplashScreen->Bind(wxEVT_CLOSE_WINDOW, &MainApplication::OnSplashClose, this);
		wxYield();

		// Return!
		return true;
	}

	// Splash screen closed
	void MainApplication::OnSplashClose(wxCloseEvent& event)
	{
		// Skip the event (destroy the splash screen)
		event.Skip();

		// Show the main application frame
		m_pMainApplicationFrame->Show();
	}
}

// Initialise the main application!
wxIMPLEMENT_APP(SimpleSELauncher::MainApplication);
