project('mesher', 'cpp', version: '0.1.0', default_options : ['warning_level=3', 'cpp_std=c++20'])

compiler      = meson.get_compiler('cpp')
sources       = ['source/mesher-units.cpp']
include       = include_directories('include')
dependencies  = [
  dependency('geometry')
  , compiler.find_library('gmsh')
  ]

mesher = library(
  meson.project_name()
  , sources
  , include_directories : include
  , dependencies        : dependencies
  , install             : true
  )

mesher_dep = declare_dependency(
  link_with             : mesher
  , include_directories : include
  , dependencies        : dependencies
  )

if not meson.is_subproject()
  subdir('example')
  subdir('tests')
endif
