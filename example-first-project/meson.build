project(
    'example-first-project',
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

src_files = files('src' / 'main.cpp')

# If macOS.
gl_dep = dependency('gl', required: true) # Installed by default in macOS.
# glu_dep = dependency('glu', required: true) # Install mesa-glu via Homebrew.
# glut_dep = dependency('glut', required: true) # Install freeglut via Homebrew.

# If Ubuntu.
# cc = meson.get_compiler('cpp')
# glut_dep = cc.find_library('glut', required : true)

glfw_proj = subproject('glfw')
glfw_dep = glfw_proj.get_variable('glfw_dep')

APP = executable(
    'app',
    src_files,
    dependencies: [
        # gl_dep,
        # glu_dep,
        # glut_dep,
        glfw_dep,
    ],
)
