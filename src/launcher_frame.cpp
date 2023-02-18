/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#include <filesystem>
#include "wx/mstream.h"
#include "wx/aboutdlg.h"
#include "launcher_frame.hpp"
#include "launcher_choice.hpp"
#include "launcher_utils.hpp"

// Embedded Icon PNG
#include "res/launcher.png.h"

// Embedded Background JPEG
#include "res/background.jpg.h"

namespace SimpleSELauncher
{
	const wxString LAUNCHER_TITLE(_T("Skyrim \"Simple\" SE Launcher"));

	// Main application frame constructor
	MainApplicationFrame::MainApplicationFrame()
		: wxFrame(nullptr, wxID_ANY, LAUNCHER_TITLE, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
	{
		// Set the background colour
		SetBackgroundColour(*wxBLACK);

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

		// Create a vertical BoxSizer for buttons
		wxBoxSizer* m_pVBoxSizer = new wxBoxSizer(wxVERTICAL);

		// Launch button, the first button visible on the Launcher
		wxButton* m_pLaunchButton = new wxButton(this, LaunchButtonID, _T("&Launch!"));
		m_pLaunchButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent& WXUNUSED(event)) {
			// Lambda - open a choice dialog
			wxArrayString choiceArray;

			// Mod Organizer (2) - in case someone spells it like this
			if (!utils::FindTargetExecutable("ModOrganiser").empty())
				choiceArray.Add(_T("Mod Organiser"));

			// Mod Organizer (2)
			if (!utils::FindTargetExecutable("ModOrganizer").empty())
				choiceArray.Add(_T("Mod Organizer"));

			// Nexus Mod Manager
			if (!utils::FindTargetExecutable("NMM").empty())
				choiceArray.Add(_T("Nexus Mod Manager"));

			// SKSE64 Loader
			if (!utils::FindTargetExecutable("skse64_loader").empty())
				choiceArray.Add(_T("SKSE64 Loader"));

			// Skyrim SE (Vanilla)
			if (!utils::FindTargetExecutable("SkyrimSE").empty())
				choiceArray.Add(_T("Skyrim SE"));

			// Skyrim SE Launcher (Vanilla)
			if (!utils::FindTargetExecutable("SkyrimSELauncher").empty())
				choiceArray.Add(_T("Skyrim SE Launcher"));

			// Skyrim Together (Client)
			if (!utils::FindTargetExecutable("SkyrimTogether").empty())
				choiceArray.Add(_T("Skyrim Together"));

			// Skyrim Together (Server)
			if (!utils::FindTargetExecutable("SkyrimTogetherServer").empty())
				choiceArray.Add(_T("Skyrim Together (Server)"));

			// Wyre Bash
			if (!utils::FindTargetExecutable("Wyre Bash").empty())
				choiceArray.Add(_T("Wyre Bash"));

			MainSingleChoiceDialog choiceDialog(this, choiceArray);
			if (!choiceArray.IsEmpty() && choiceDialog.ShowModal() == wxID_OK)
			{
				std::filesystem::path exePath(utils::FindTargetExecutable(utils::PrettyNameToFileName(choiceDialog.GetStringSelection().ToStdString())));
				if (utils::ExecuteProgram(exePath.wstring(), L"", exePath.parent_path().wstring(), false))
					this->Close();
			}
			else if (choiceArray.IsEmpty())
			{
				wxMessageBox(_T("I found nothing..\n\nbut I found my coffee cup!"), _T("Nothing Found!"), wxOK | wxICON_ERROR, this);
				choiceDialog.Destroy();
			}
		}, LaunchButtonID);
		m_pVBoxSizer->Add(m_pLaunchButton, 0, wxALL, 5);

		// MSVC button, the second button visible on the Launcher
		wxButton* m_pMSVCButton = new wxButton(this, MSVCButtonID, _T("&MSVC++"));
		m_pMSVCButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent& WXUNUSED(event)) {
			// Lambda - open a choice dialog
			wxArrayString choiceArray;

			// MSVC++ Redistributable (x86-64)
			if (!utils::FindTargetExecutable("VC_redist.x64.exe").empty())
				choiceArray.Add(_T("MSVC++ Redistributable x64"));

			// MSVC++ Redistributable (x86)
			if (!utils::FindTargetExecutable("VC_redist.x86.exe").empty())
				choiceArray.Add(_T("MSVC++ Redistributable x86"));

			MainSingleChoiceDialog choiceDialog(this, choiceArray);
			if (!choiceArray.IsEmpty() && choiceDialog.ShowModal() == wxID_OK)
			{
				std::filesystem::path exePath(utils::FindTargetExecutable(utils::PrettyNameToFileName(choiceDialog.GetStringSelection().ToStdString())));
				if (utils::ExecuteProgram(exePath.wstring(), L"/install /passive /norestart", exePath.parent_path().wstring(), true))
					choiceDialog.Destroy();
			}
			else if (choiceArray.IsEmpty())
			{
				wxMessageBox(_T("I found nothing..\n\nbut I found my coffee cup!"), _T("Nothing Found!"), wxOK | wxICON_ERROR, this);
				choiceDialog.Destroy();
			}
		}, MSVCButtonID);
		m_pVBoxSizer->Add(m_pMSVCButton, 0, wxALL, 5);
		m_pVBoxSizer->AddStretchSpacer(1);

		// About button, the third button visible on the Launcher
		wxButton* m_pAboutButton = new wxButton(this, wxID_ABOUT, _T("&About"));
		m_pAboutButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent& WXUNUSED(event)) {
			// Lambda - create an About dialog window
			wxAboutDialogInfo info;
			info.SetIcon(iconIco);
			info.SetName(LAUNCHER_TITLE);
			info.SetVersion(_T("v1.0"));
			info.SetDescription(_T("This is a custom Launcher application for Skyrim SE.\nIt allows the user to override the default launch executable and launch another *known* application, such as Mod Organizer.\n\n\nwxWidgets is licensed under the 'wxWindows Library License'.\nBoost Library is licensed under the 'Boost Software License'.\nSKYRIM is a trademark of ZeniMax Media Inc.."));
			info.SetCopyright(_T("(c) 2023 Jai \"Choccy\" Fox"));
			wxAboutBox(info, this);
		}, wxID_ABOUT);
		m_pVBoxSizer->Add(m_pAboutButton, 0, wxALL, 5);

		// Exit button, the last button visible on the Launcher
		wxButton* m_pExitButton = new wxButton(this, wxID_EXIT, _T("&Exit"));
		m_pExitButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent& WXUNUSED(event)) {
			// Lambda - close the frame (stops the application)
			this->Close();
		}, wxID_EXIT);
		m_pVBoxSizer->Add(m_pExitButton, 0, wxALL, 5);

		// Finally, attach the BoxSizers
		m_pBoxSizer->Add(m_pVBoxSizer, 0, wxALL | wxEXPAND, 10);
		m_pBoxSizer->SetSizeHints(this);
		this->SetSizerAndFit(m_pBoxSizer);

		// Disable the Launch & MSVC buttons on non-Windows platforms, in case someone does compile this for another platform
#if !defined(__WIN32__)
		m_pLaunchButton->Disable();
		m_pMSVCButton->Disable();
#endif
	}
}
