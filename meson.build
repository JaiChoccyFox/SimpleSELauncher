project('SimpleSELauncher', 'cpp', version: 'v1.0', meson_version: '>=0.56.0', default_options: [
  'cpp_std=c++17',
  'warning_level=3'
])

platform = target_machine.system()
cpp_compiler = meson.get_compiler('cpp')
linker_args = []

if platform == 'windows'
  if cpp_compiler.get_id() == 'msvc'
    add_project_arguments('/DWIN32', language: 'cpp')
    add_project_arguments('/D_WIN32', language: 'cpp')
    add_project_arguments('/D__WIN32', language: 'cpp')
    add_project_arguments('/D__WIN32__', language: 'cpp')
    add_project_arguments('/DUNICODE', language: 'cpp')
    add_project_arguments('/D_UNICODE', language: 'cpp')
  else
    add_project_arguments('-DWIN32', language: 'cpp')
    add_project_arguments('-D_WIN32', language: 'cpp')
    add_project_arguments('-D__WIN32', language: 'cpp')
    add_project_arguments('-D__WIN32__', language: 'cpp')
    add_project_arguments('-DUNICODE', language: 'cpp')
    add_project_arguments('-D_UNICODE', language: 'cpp')

    linker_args += [
      '-static',
      '-static-libgcc',
      '-static-libstdc++'
    ]
  endif
endif

boost_dep = dependency('Boost', required: true, modules: ['filesystem'])
wx_dep = dependency('WxWidgets', required: true, modules: ['std', 'stc'])

subdir('src')
