#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "config.h"
#include "shaders.h"
#include "texture.h"
#include "draw.h"
#include "renderer.h"
#include "window.h"
#include "log.h"
#include "gameplay.h"
#include "viewer.h"
#include "mouse.h"  // Include mouse for callback setup
#include "input_handler.h"
#include "game/gameplay/gameplay_log.h"

extern Logger logger;
extern std::vector<Piece*> pieces;  // Define the global pieces vector

int main() {
    logger.log(LogLevel::INFO, "Starting application...");

    // Initialize the gameplay logs
    initializeLogs();
    gameplayLogger.log(LogLevel::INFO, "Gameplay logs initialized.");

    logConfigValues(); // Log the configuration values here

    if (!glfwInit()) {
        logger.log(LogLevel::CRITICAL, "Failed to initialize GLFW!");
        gameplayLogger.log(LogLevel::CRITICAL, "Failed to initialize GLFW!");
        return -1;
    }
    logger.log(LogLevel::INFO, "GLFW initialized successfully.");
    gameplayLogger.log(LogLevel::INFO, "GLFW initialized successfully.");

    GLFWwindow* window = createWindow(800, 800, "Chessboard");
    if (!window) {
        logger.log(LogLevel::CRITICAL, "Failed to create GLFW window!");
        gameplayLogger.log(LogLevel::CRITICAL, "Failed to create GLFW window!");
        return -1;
    }
    logger.log(LogLevel::INFO, "GLFW window created successfully.");
    gameplayLogger.log(LogLevel::INFO, "GLFW window created successfully.");

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        logger.log(LogLevel::CRITICAL, "Failed to initialize GLEW!");
        gameplayLogger.log(LogLevel::CRITICAL, "Failed to initialize GLEW!");
        return -1;
    }
    logger.log(LogLevel::INFO, "GLEW initialized successfully.");
    gameplayLogger.log(LogLevel::INFO, "GLEW initialized successfully.");

    unsigned int shaderProgram = loadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    if (!shaderProgram) {
        logger.log(LogLevel::CRITICAL, "Failed to load shaders!");
        gameplayLogger.log(LogLevel::CRITICAL, "Failed to load shaders!");
        return -1;
    }
    logger.log(LogLevel::INFO, "Shaders loaded successfully. Shader Program ID: " + std::to_string(shaderProgram));
    gameplayLogger.log(LogLevel::INFO, "Shaders loaded successfully. Shader Program ID: " + std::to_string(shaderProgram));

    glfwSetWindowUserPointer(window, &shaderProgram);

    initializeViewport(window);  // Set up the viewport
    setupMouseCallback(window);  // Set up the mouse callback

    initializeRenderer(shaderProgram, window);
    logger.log(LogLevel::INFO, "Renderer initialized.");
    gameplayLogger.log(LogLevel::INFO, "Renderer initialized.");

    // Set the key callback function for adjusting parameters
    glfwSetKeyCallback(window, keyCallback);

    unsigned int boardTextures[2];
    boardTextures[0] = loadTexture(LIGHT_SQUARE_TEXTURE_PATH);
    boardTextures[1] = loadTexture(DARK_SQUARE_TEXTURE_PATH);
    if (!boardTextures[0] || !boardTextures[1]) {
        logger.log(LogLevel::CRITICAL, "Failed to load board textures!");
        gameplayLogger.log(LogLevel::CRITICAL, "Failed to load board textures!");
        return -1;
    }
    logger.log(LogLevel::INFO, "Board textures loaded successfully.");
    gameplayLogger.log(LogLevel::INFO, "Board textures loaded successfully.");

    // Setup the pieces
    setupPieces(pieces);
    logPiecePositions(pieces);  // Log the initial positions of the pieces
    gameplayLogger.log(LogLevel::INFO, "Pieces setup completed.");

    logger.log(LogLevel::DEBUG, "Entering rendering loop...");
    gameplayLogger.log(LogLevel::DEBUG, "Entering rendering loop...");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawChessboard(shaderProgram, boardTextures, legalMoves); // Draw the chessboard with possible moves highlighted
        drawAllPieces(shaderProgram, pieces);  // Draw all the pieces

        glfwPollEvents();
        updateWindow(window);
    }

    // Cleanup dynamically allocated pieces
    for (Piece* piece : pieces) {
        delete piece;
    }

    logger.log(LogLevel::INFO, "Terminating application...");
    gameplayLogger.log(LogLevel::INFO, "Terminating application...");
    glfwTerminate();
    logger.log(LogLevel::INFO, "Application terminated.");
    gameplayLogger.log(LogLevel::INFO, "Application terminated.");

    return 0;
}
