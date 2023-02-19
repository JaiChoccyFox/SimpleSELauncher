/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#pragma once

#include <wx/wxprec.h>

#if !defined(WX_PRECOMP)
	#include <wx/wx.h>
#endif

namespace SimpleSELauncher
{
	class MainApplicationFrame : public wxFrame
	{
		public:
			MainApplicationFrame();

		private:
			enum ButtonID
			{
				LaunchButtonID = 69,  // Funny, right!?
				MSVCButtonID = 70
			};
	};
}
