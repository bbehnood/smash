project(
  'smash',
  'c',
  default_options: [
    'c_std=c11',
    'warning_level=3' 
  ]
)

add_project_arguments(
  '-D_POSIX_C_SOURCE=200809L',
  language: 'c'
)

src = files(
  'src/main.c',
  'src/token.c',
)

inc = include_directories('src')

executable(
  'smash',
  src,
  include_directories: inc,
)
