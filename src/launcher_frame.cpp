/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#include "wx/mstream.h"
#include "launcher_frame.hpp"

// Embedded Icon PNG
#include "res/launcher.png.h"

// Embedded Background JPEG
#include "res/background.jpg.h"

namespace SimpleSELauncher
{
	const wxString LAUNCHER_TITLE("Skyrim \"Simple\" SE Launcher");
	const wxSize LAUNCHER_SIZE(800, 600);

	MainApplicationFrame::MainApplicationFrame()
		: wxFrame(NULL, wxID_ANY, LAUNCHER_TITLE, wxDefaultPosition, LAUNCHER_SIZE, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
	{
		// Load Icon PNG into memory
		wxMemoryInputStream iconData(LAUNCHER_PNG, sizeof(LAUNCHER_PNG));
		wxImage iconImg(iconData, wxBITMAP_TYPE_PNG);
		wxBitmap iconBmp(iconImg);
		wxIcon iconIco;
		iconIco.CopyFromBitmap(iconBmp);

		// Set the frame icon
		SetIcon(iconIco);

		// Create a BoxSizer for the Launcher layout
		wxBoxSizer* m_pBoxSizer = new wxBoxSizer(wxHORIZONTAL);
		m_pBoxSizer->SetSizeHints(this);
		this->SetSizer(m_pBoxSizer);

		// Load Background JPEG into memory
		wxMemoryInputStream backgroundData(BACKGROUND_JPG, sizeof(BACKGROUND_JPG));
		wxImage backgroundImg(backgroundData, wxBITMAP_TYPE_JPEG);
		wxBitmap backgroundBmp(backgroundImg);

		// Create a static bitmap to display
		wxStaticBitmap* m_pStaticBackgroundBmp = new wxStaticBitmap(this, wxID_ANY, backgroundBmp);
		m_pBoxSizer->Add(m_pStaticBackgroundBmp, 0);

		// Set a minimum window size (minimum is that of the background resolution)
		SetMinSize(LAUNCHER_SIZE);

#if !defined(WIN32)
		// This is a Windows-only launcher. If we are somehow on another platform, warn the user
		wxMessageBox("You are running the Launcher on a non-Windows platform!\n\nLaunching has been disabled.", "Platform Error", wxOK | wxICON_ERROR, this);
#endif
	}
}
