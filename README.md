# Skyrim "Simple" SE Launcher
**Skyrim "Simple" SE Launcher** is a custom launcher for *Skyrim Special Edition*.
It acts as a drop-in replacement for the already existing ***`SkyrimSELauncher.exe`*** executable that can be located in the main installation directory.

It's simple but allows for users to choose what they wish to launch, and may prove useful for users who use Linux + Proton.

## Building
On Windows (MSYS2), make sure `Boost` & `wxWidgets` are available to satisfy the dependencies! Run the following to build:
```
meson setup --strip --buildtype release --prefix "${PWD}/build.prefix" "build.win64"
meson compile -C "build.win64"
meson install -C "build.win64"```

On Linux (w/ MinGW), make sure `Boost` & `wxWidgets` are available to satisfy the dependencies! Run the following to build:
```
meson setup --strip --buildtype release --cross-file "./cross/x86_64-w64-mingw32.txt" --prefix "${PWD}/build.prefix" "build.win64"
meson compile -C "build.win64"
meson install -C "build.win64"```

## Installation
Rename the default ***`SkyrimSELauncher.exe`*** to something like ***`SkyrimSELauncher.old.exe`*** and drag-and-drop this launcher into its place.

Once you complete the step, a different window should appear.
Clicking "Launch" will bring up an additional window for you to select what application to execute (if it exists.)


You can launch any of these:
* Mod Organizer
* Nexus Mod Manager
* SKSE64 Loader
* Skyrim SE
* Skyrim SE Launcher
* Skyrim Together
* Skyrim Together (Server)
* Wyre Bash
