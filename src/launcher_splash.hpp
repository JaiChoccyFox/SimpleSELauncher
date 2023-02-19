/* =======================================================
 *              Skyrim "Simple" SE Launcher
 *               (c) 2023 Jai "Choccy" Fox
 * ======================================================= */
#pragma once

#include <wx/wxprec.h>

#if !defined(WX_PRECOMP)
	#include <wx/wx.h>
#endif

#include <wx/splash.h>

namespace SimpleSELauncher
{
	class MainSplashScreen : public wxSplashScreen
	{
		public:
			MainSplashScreen(const wxBitmap &bitmap);
	};
}
