/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#include "wx/mstream.h"
#include "wx/aboutdlg.h"
#include "launcher_frame.hpp"

// Embedded Icon PNG
#include "res/launcher.png.h"

// Embedded Title PNG
#include "res/title.png.h"

// Embedded Background JPEG
#include "res/background.jpg.h"

namespace SimpleSELauncher
{
	const wxString LAUNCHER_TITLE("Skyrim \"Simple\" SE Launcher");

	// Main application frame constructor
	MainApplicationFrame::MainApplicationFrame()
		: wxFrame(NULL, wxID_ANY, LAUNCHER_TITLE, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
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

		// Load Background JPEG into memory
		wxMemoryInputStream backgroundData(BACKGROUND_JPG, sizeof(BACKGROUND_JPG));
		wxImage backgroundImg(backgroundData, wxBITMAP_TYPE_JPEG);
		wxBitmap backgroundBmp(backgroundImg);

		// Create a static bitmap to display the Background
		wxStaticBitmap* m_pStaticBackgroundBmp = new wxStaticBitmap(this, wxID_ANY, backgroundBmp);
		m_pBoxSizer->Add(m_pStaticBackgroundBmp, 0, wxALL | wxEXPAND, 0);

		// Load Title PNG into memory
		wxMemoryInputStream titleData(TITLE_PNG, sizeof(TITLE_PNG));
		wxImage titleImg(titleData, wxBITMAP_TYPE_PNG);
		wxBitmap titleBmp(titleImg);

		// Create a static bitmap to display the Title
		wxStaticBitmap* m_pStaticTitleBmp = new wxStaticBitmap(this, wxID_ANY, titleBmp);

		// Create a vertical BoxSizer for buttons
		wxBoxSizer* m_pVBoxSizer = new wxBoxSizer(wxVERTICAL);

		// Launch button, the first button visible on the Launcher
		wxButton* m_pLaunchButton = new wxButton(this, LaunchButtonID, "&Launch!");
		m_pVBoxSizer->Add(m_pLaunchButton, 0, wxALL, 5);
		m_pVBoxSizer->AddStretchSpacer(1);

		// About button, the second button visible on the Launcher
		wxButton* m_pAboutButton = new wxButton(this, wxID_ABOUT, "&About");
		m_pAboutButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent& WXUNUSED(event)) {
			// Lambda - create an About dialog window
			wxAboutDialogInfo info;
			info.SetIcon(iconIco);
			info.SetName(LAUNCHER_TITLE);
			info.SetVersion("v1.0");
			info.SetDescription("This is a custom Launcher application for Skyrim SE. It allows the user to override the default launch executable and launch another *known* application, such as Mod Organizer.\n\n\nwxWidgets is licensed under the 'wxWindows Library License'.\nSKYRIM is a trademark of ZeniMax Media Inc..");
			info.SetCopyright("(c) 2023 Jai \"Choccy\" Fox");
			wxAboutBox(info, this);
		}, wxID_ABOUT);
		m_pVBoxSizer->Add(m_pAboutButton, 0, wxALL, 5);

		// Exit button, the last button visible on the Launcher
		wxButton* m_pExitButton = new wxButton(this, wxID_EXIT, "&Exit");
		m_pExitButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent& WXUNUSED(event)) {
			// Lambda - close the frame and stop the application
			this->Close();
		}, wxID_EXIT);
		m_pVBoxSizer->Add(m_pExitButton, 0, wxALL, 5);

		// Finally, attach the BoxSizers
		m_pBoxSizer->Add(m_pVBoxSizer, 0, wxALL | wxEXPAND, 10);
		m_pBoxSizer->SetSizeHints(this);
		this->SetSizerAndFit(m_pBoxSizer);

		// HACK: centre the Title bitmap with the Background, this is dumb but I got segmentation faults with other methods
		m_pStaticTitleBmp->SetParent(m_pStaticBackgroundBmp);
		m_pStaticTitleBmp->CentreOnParent();
		m_pStaticTitleBmp->SetParent(this);
	}
}
