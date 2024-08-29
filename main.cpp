#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "config.h"
#include "shaders.h"
#include "texture.h"
#include "chessboard.h"
#include "renderer.h"
#include "window.h"
#include "log.h"  // Include the logger

extern Logger logger;  // Use the global logger

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    logger.log(LogLevel::INFO, "Framebuffer size changed: " + std::to_string(width) + "x" + std::to_string(height));
    resizeRenderer(glGetUniformLocation(*(unsigned int*)glfwGetWindowUserPointer(window), "projection"), width, height);
    setViewport(window);
    logger.log(LogLevel::TRACE, "Framebuffer size callback executed.");
}

int main() {
    logger.log(LogLevel::INFO, "Starting application...");

    logConfigValues(); // Log the configuration values here

    if (!glfwInit()) {
        logger.log(LogLevel::CRITICAL, "Failed to initialize GLFW!");
        return -1;
    }
    logger.log(LogLevel::INFO, "GLFW initialized successfully.");

    GLFWwindow* window = createWindow(800, 800, "Chessboard");
    if (!window) {
        logger.log(LogLevel::CRITICAL, "Failed to create GLFW window!");
        return -1;
    }
    logger.log(LogLevel::INFO, "GLFW window created successfully.");

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        logger.log(LogLevel::CRITICAL, "Failed to initialize GLEW!");
        return -1;
    }
    logger.log(LogLevel::INFO, "GLEW initialized successfully.");

    unsigned int shaderProgram = loadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    if (!shaderProgram) {
        logger.log(LogLevel::CRITICAL, "Failed to load shaders!");
        return -1;
    }
    logger.log(LogLevel::INFO, "Shaders loaded successfully. Shader Program ID: " + std::to_string(shaderProgram));

    glfwSetWindowUserPointer(window, &shaderProgram);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    initializeRenderer(shaderProgram, window);
    logger.log(LogLevel::INFO, "Renderer initialized.");

    unsigned int boardTextures[2];
    boardTextures[0] = loadTexture(LIGHT_SQUARE_TEXTURE_PATH);
    boardTextures[1] = loadTexture(DARK_SQUARE_TEXTURE_PATH);
    if (!boardTextures[0] || !boardTextures[1]) {
        logger.log(LogLevel::CRITICAL, "Failed to load board textures!");
        return -1;
    }
    logger.log(LogLevel::INFO, "Board textures loaded successfully.");

    unsigned int pieceTexture = loadTexture(PIECE_TEXTURE_PATH);
    if (!pieceTexture) {
        logger.log(LogLevel::CRITICAL, "Failed to load piece texture!");
        return -1;
    }
    logger.log(LogLevel::INFO, "Piece texture loaded successfully.");

    logger.log(LogLevel::DEBUG, "Entering rendering loop...");
    while (!glfwWindowShouldClose(window)) {
        logger.log(LogLevel::FRAME, "Rendering frame...");

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawChessboard(shaderProgram, boardTextures, pieceTexture);

        updateWindow(window);
        logger.log(LogLevel::FRAME, "Frame displayed and events polled.");
    }

    logger.log(LogLevel::INFO, "Terminating application...");
    glfwTerminate();
    logger.log(LogLevel::INFO, "Application terminated.");
    return 0;
}
