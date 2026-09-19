project(
  'smash',
  'c',
  default_options: [
    'c_std=c11',
    'warning_level=3' 
  ]
)

add_project_arguments(
  language: 'c'
)

src = files(
  'src/main.c',
)

inc = include_directories('src')

executable(
  'smash',
  src,
  include_directories: inc,
)
