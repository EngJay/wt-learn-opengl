/**
 * @file main.cpp
 * @brief Main file containing the main entry point of the application.
 *
 * @author Jason Scott
 * @date 2 July 2024
 *
 * @copyright Copyright (c) 2024
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>

#define UNUSED(x) (void)(x) //!< Voids unused parameters to resolve unnused parameters warnings.

/**
 * @brief The most basic vertex shader source as a string.
 *
 * This shader does no processing; it just forwards the data to the output.
 */
const char *vertexShaderSource = "#version 330 core \n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "  gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

/**
 * @brief The most basic fragment shader source as a string.
 *
 * This shader does no processing; it always outputs an orange-ish color.
 *
 */
const char *fragmentShaderSource = "#version 330 core \n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

/**
 * @brief Handler for resizing of the viewport with resizing of the window.
 *
 * @param window instance of the window being resized
 * @param width width of the window
 * @param height height of the window
 */
void framebufferSizeCallback(GLFWwindow *window, int width, int height);

/**
 * @brief Handler for input to the window.
 *
 * @param window instance of the window receiving the input
 */
void processInput(GLFWwindow *window);

const unsigned int WINDOW_WIDTH = 800;  //!< Window width.
const unsigned int WINDOW_HEIGHT = 600; //!< Window height.

int main()
{
    // Init and configure glwf.
    //
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create a window / context using GLFW.
    //
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Work-Through: Learn OpenGL  |  Hello Window!", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback); // Set handler resizing.

    // Init GLAD to get function pointers for OpenGL.
    //
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Build shader program here for simplicity.
    //
    // Shaders are compiled and linked together into a kind of shader program,
    // then used by OpenGL.
    //
    // Compile the vertex shader.
    //
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Ensure vertex shader compiled successfully.
    //
    int successful;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successful);
    if (!successful)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infolog << std::endl;
    }

    // Compile the fragment shader.
    //
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Ensure fragment shader compiled successfully.
    //
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successful);
    if (!successful)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infolog << std::endl;
    }

    // Now that we have shaders, we link them into a shader program.
    //
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Ensure the shader program built successfully.
    //
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successful);
    if (!successful)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infolog << std::endl;
    }

    // Set the shader program in OpenGL.
    //
    glUseProgram(shaderProgram);

    // Clean up - source objects are no longer needed.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // End build of shader program.

    // Set color for opengl to use to clear the buffer.
    //
    // NOTE: This was not included in the book example. Without this, the window
    //       flickered rapidly between red and black.
    //
    // glClear(GL_COLOR_BUFFER_BIT);

    // Rendering loop.
    //
    // An iteration of the loop is typically referred to as a frame.
    //
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // I changed this to a nicer color than the ugly green set in the book.
        glClearColor(0.0f, 0.145f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Check events, then swap the front/back buffers.
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Clean up.
    //
    glfwTerminate();

    return EXIT_SUCCESS;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    UNUSED(window);
}
