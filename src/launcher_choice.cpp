/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#include <vector>
#include "launcher_choice.hpp"

namespace SimpleSELauncher
{
	// Choice dialog constructor
	MainSingleChoiceDialog::MainSingleChoiceDialog(wxWindow* parent, const wxArrayString& choices)
		: wxSingleChoiceDialog(parent, _T("Launch:"), _T("Launcher"), choices)
	{
	}
}
