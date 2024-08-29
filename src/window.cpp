#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "log.h"  // Include the logger

extern Logger logger;  // Use the global logger

GLFWwindow* createWindow(int width, int height, const char* title) {
    logger.log(LogLevel::INFO, "Creating window with size: " + std::to_string(width) + "x" + std::to_string(height));

    if (!glfwInit()) {
        logger.log(LogLevel::CRITICAL, "Failed to initialize GLFW.");
        return nullptr;
    }
    logger.log(LogLevel::INFO, "GLFW initialized successfully.");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        logger.log(LogLevel::CRITICAL, "Failed to create GLFW window.");
        glfwTerminate();
        return nullptr;
    }
    logger.log(LogLevel::INFO, "GLFW window created successfully.");

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        logger.log(LogLevel::CRITICAL, "Failed to initialize GLEW.");
        return nullptr;
    }
    logger.log(LogLevel::INFO, "GLEW initialized successfully.");

    return window;
}

void updateWindow(GLFWwindow* window) {
    logger.log(LogLevel::TRACE, "Updating window.");

    glfwSwapBuffers(window);
    glfwPollEvents();
}