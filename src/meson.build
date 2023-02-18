src_files = files([
  'launcher_main.cpp',
  'launcher_splash.cpp',
  'launcher_frame.cpp',
  'launcher_choice.cpp',
  'launcher_utils.cpp'
])

if platform == 'windows'
  # HACK: Include directories are not passed to the Windows module...
  wx_dep_cppflags = wx_dep.get_variable(configtool: 'cppflags')
  wx_dep_cppflags_array = wx_dep_cppflags.split(' ')

  windows = import('windows')
  src_files += windows.compile_resources('launcher.rc', args: wx_dep_cppflags_array)
endif

exe = executable('SkyrimSELauncher', src_files, link_args: linker_args, dependencies: [boost_dep, wx_dep], win_subsystem: 'windows,6.0', install: true)
