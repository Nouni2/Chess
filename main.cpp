#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "shader.h"
#include "chessboard.h"

// Window dimensions
const GLuint WIDTH = 1000, HEIGHT = 1000;

int main(int argc, char** argv) {
    // Initialize GLFW and create a window
    GLFWwindow* window = initWindow(WIDTH, HEIGHT, "Chess Board");
    if (!window) {
        return -1;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Set the viewport
    glViewport(0, 0, WIDTH, HEIGHT);

    // Load and compile shaders
    std::string vertexShaderSource = loadShaderSource("shaders/vertex_shader.glsl");
    std::string fragmentShaderSource = loadShaderSource("shaders/fragment_shader.glsl");
    GLuint shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Check for events
        glfwPollEvents();

        // Clear the screen
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);

        // Render the chessboard
        drawChessboard(shaderProgram);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
