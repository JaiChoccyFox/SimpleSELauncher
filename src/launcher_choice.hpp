/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#pragma once

#include "wx/wxprec.h"

#if !defined(WX_PRECOMP)
	#include "wx/wx.h"
#endif

namespace SimpleSELauncher
{
	class MainSingleChoiceDialog : public wxSingleChoiceDialog
	{
		public:
			MainSingleChoiceDialog(wxWindow* parent, const wxArrayString& choices);
	};
}
