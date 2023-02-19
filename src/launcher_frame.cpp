/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#include <array>
#include <boost/process.hpp>
#include <wx/mstream.h>
#include <wx/aboutdlg.h>
#include "launcher_frame.hpp"
#include "launcher_choice.hpp"
#include "launcher_utils.hpp"

// Embedded Icon PNG
#include "res/launcher.png.h"

// Embedded Background JPEG
#include "res/background.jpg.h"

namespace process = boost::process;
namespace dll = boost::dll;
namespace filesystem = boost::filesystem;
using std::wstring;
using std::array;
using std::vector;
using process::spawn;
using process::child;
using process::start_dir;
using dll::program_location;
using filesystem::path;

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
		wxBoxSizer *m_pBoxSizer = new wxBoxSizer(wxHORIZONTAL);

		// Load Background JPEG into memory
		wxMemoryInputStream backgroundData(BACKGROUND_JPG, sizeof(BACKGROUND_JPG));
		wxImage backgroundImg(backgroundData, wxBITMAP_TYPE_JPEG);
		wxBitmap backgroundBmp(backgroundImg);

		// Create a static bitmap to display the Background
		wxStaticBitmap *m_pStaticBackgroundBmp = new wxStaticBitmap(this, wxID_ANY, backgroundBmp);
		m_pBoxSizer->Add(m_pStaticBackgroundBmp, 0, wxALL | wxEXPAND, 0);

		// Create a vertical BoxSizer for buttons
		wxBoxSizer *m_pVBoxSizer = new wxBoxSizer(wxVERTICAL);

		// Launch button, the first button visible on the Launcher
		wxButton *m_pLaunchButton = new wxButton(this, LaunchButtonID, _T("&Launch!"));
		m_pLaunchButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent &WXUNUSED(event)) {
			// Lambda - open a choice dialog
			const array<wstring, 11> nameArray = {
				L"ModOrganiser.",
				L"ModOrganizer.",
				L"NMM-",
				L"skse64_loader.",
				L"SkyrimSE.",
				L"SkyrimSELauncher.",
				L"SkyrimTogether.",
				L"SkyrimTogetherServer.",
				L"Vortex.",
				L"WyreBash.",
				L"Wyre Bash."
			};
			vector<path> choiceVector;
			wxArrayString choiceArray;

			for (const wstring &s : nameArray)
				utils::FindTargetExecutable(program_location().parent_path(), s, choiceVector);

			for (const path &p : choiceVector)
				choiceArray.Add(filesystem::relative(p).native());

			MainSingleChoiceDialog choiceDialog(this, choiceArray);
			if (!choiceArray.IsEmpty() && choiceDialog.ShowModal() == wxID_OK)
			{
				const path choicePath(choiceDialog.GetStringSelection().wc_str());
				spawn(filesystem::canonical(choicePath), start_dir(filesystem::canonical(choicePath.parent_path())));
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
		wxButton *m_pMSVCButton = new wxButton(this, MSVCButtonID, _T("&MSVC++"));
		m_pMSVCButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent &WXUNUSED(event)) {
			// Lambda - open a choice dialog
			const array<wstring, 4> nameArray = {
				L"VC_redist.x64.",
				L"VC_redist.x86.",
				L"vcredist_x64.",
				L"vcredist_x86."
			};
			vector<path> choiceVector;
			wxArrayString choiceArray;

			for (const wstring &str : nameArray)
				utils::FindTargetExecutable(program_location().parent_path(), str, choiceVector);

			for (const path &p : choiceVector)
				choiceArray.Add(filesystem::relative(p).native());

			MainSingleChoiceDialog choiceDialog(this, choiceArray);
			if (!choiceArray.IsEmpty() && choiceDialog.ShowModal() == wxID_OK)
			{
				const path choicePath(choiceDialog.GetStringSelection().wc_str());
				child cp(filesystem::canonical(choicePath), "/install /passive /norestart", start_dir(filesystem::canonical(choicePath.parent_path())));
				while (cp.running())
					wxSleep(1);
				cp.wait();
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
		wxButton *m_pAboutButton = new wxButton(this, wxID_ABOUT, _T("&About"));
		m_pAboutButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent &WXUNUSED(event)) {
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
		wxButton *m_pExitButton = new wxButton(this, wxID_EXIT, _T("&Exit"));
		m_pExitButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent &WXUNUSED(event)) {
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
