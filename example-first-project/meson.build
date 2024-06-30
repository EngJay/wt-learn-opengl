project(
    'example-first-project',
    'c',
    'cpp',
    default_options: [
        'debug=false', # Defaults to release build.
        'warning_level=3',
        'optimization=2',
        # `build.*` options affect `native: true targets`,
        # plain options affect `native: false` targets.
        'c_std=c11',
        'build.c_std=c11',
        'cpp_std=c++11',
        'build.cpp_std=c++11',
    ],
    # meson_version: '>=1.1.0',
    version: '0.1.0',
)

src_dir = 'src'
ext_dir = src_dir / 'ext'

src_files = files(src_dir / 'main.cpp', ext_dir / 'glad' / 'src' / 'glad.c')

inc_dirs = include_directories(src_dir, ext_dir / 'glad' / 'include')

# For all.
gl_dep = dependency('gl', required: true) # Installed by default in macOS.
# glu_dep = dependency('glu', required: true) # Install mesa-glu via Homebrew.
# glut_dep = dependency('glut', required: true) # Install freeglut via Homebrew.

# If Ubuntu.
# cc = meson.get_compiler('cpp')
# glut_dep = cc.find_library('glut', required : true)

glfw_proj = subproject('glfw')
glfw_dep = glfw_proj.get_variable('glfw_dep')

executable_name = 'example-first-project'

APP = executable(
    executable_name,
    sources: src_files,
    include_directories: inc_dirs,
    # link_args: [cpp_l_flags],
    dependencies: [
        glfw_dep,
    ],
    cpp_args: [], # C flags are added directly by the check-and-apply-flags module.
    c_args: [], # C flags are added directly by the check-and-apply-flags module.
)
