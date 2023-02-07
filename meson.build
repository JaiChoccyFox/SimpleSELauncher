project('SimpleSELauncher', 'cpp', version: 'v1.0', meson_version: '>=0.56.0', default_options: [
  'buildtype=release',
  'strip=true',
  'cpp_std=c++17',
  'warning_level=3'
])

platform = target_machine.system()
linker_args = []

if platform == 'windows'
  linker_args += [
    '-static',
    '-static-libgcc',
    '-static-libstdc++'
  ]
endif

wx_dep = dependency('wxWidgets', native: true, modules: ['std', 'stc'])

subdir('src')
