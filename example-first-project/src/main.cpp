/**
 * @file main.cpp
 * @brief Main file containing the main entry point of the application.
 *
 * @author Jason Scott
 * @date 30 June 2024
 *
 * @copyright Copyright (c) 2024
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>

#define UNUSED(x) (void)(x) //!< Voids unused parameters to resolve unnused parameters warnings.

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
