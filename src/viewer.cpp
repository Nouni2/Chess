#include <GL/glew.h>
#include "viewer.h"
#include "log.h"
#include "renderer.h"
#include "config.h"


extern Logger logger;  // Use the global logger

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    logger.log(LogLevel::INFO, "Framebuffer size changed: " + std::to_string(width) + "x" + std::to_string(height));

    // Calculate the aspect ratio of the window
    float aspectRatio = (float)width / (float)height;
    float boardAspectRatio = 1.0f; // Since the chessboard is square

    int viewportWidth, viewportHeight;
    if (aspectRatio >= boardAspectRatio) {
        // Window is wider than the board, adjust the width
        viewportWidth = height * boardAspectRatio;
        viewportHeight = height;
    } else {
        // Window is taller than the board, adjust the height
        viewportWidth = width;
        viewportHeight = width / boardAspectRatio;
    }

    // Set the viewport centered in the window
    int viewportX = (width - viewportWidth) / 2;
    int viewportY = (height - viewportHeight) / 2;

    glViewport(viewportX, viewportY, viewportWidth, viewportHeight);

    resizeRenderer(glGetUniformLocation(*(unsigned int*)glfwGetWindowUserPointer(window), "projection"), width, height);
    setViewport(window);
    logger.log(LogLevel::TRACE, "Framebuffer size callback executed.");
}

void initializeViewport(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    framebuffer_size_callback(window, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}
