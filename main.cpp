#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include "config.h"
#include "shaders.h"
#include "texture.h"
#include "draw.h"
#include "renderer.h"
#include "window.h"
#include "log.h"
#include "gameplay.h"
#include "viewer.h"
#include "mouse.h"
#include "memory.h"
#include "input_handler.h"
#include "game/gameplay/gameplay_log.h"
#include "game/game_state.h"
#include "benchmark.h"

extern Logger logger;

GameState gameState;      // Central game state (owns all pieces)
Memory gameMemory;        // Memory object to track moves

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
    setupPieces(gameState.pieces);
    logPiecePositions(gameState.pieces);
    gameplayLogger.log(LogLevel::INFO, "Pieces setup completed.");

    logger.log(LogLevel::DEBUG, "Entering rendering loop...");
    gameplayLogger.log(LogLevel::DEBUG, "Entering rendering loop...");

    // ── BENCHMARK MODE (uncomment to run benchmark) ─────────────────────────
    // runBenchmark(window, shaderProgram, boardTextures, gameState.pieces, gameState.legalMoves);
    // ── Normal game loop ──────────────────────────────────────────────────────
    auto startTime = std::chrono::high_resolution_clock::now();
    int frameCount = 0;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawChessboard(shaderProgram, boardTextures, gameState.legalMoves);
        drawAllPieces(shaderProgram, gameState.pieces);
        glfwPollEvents();
        updateWindow(window);
        if (showFPS) {
            frameCount++;
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = currentTime - startTime;
            if (duration.count() >= 1.0f) {
                float fps = frameCount / duration.count();
                glfwSetWindowTitle(window, ("Chessboard - FPS: " + std::to_string(fps)).c_str());
                frameCount = 0;
                startTime = currentTime;
            }
        }
    }

    // Cleanup OpenGL resources
    for (const auto& piece : gameState.pieces) {
        unsigned int tex = piece->getTexture();
        glDeleteTextures(1, &tex);
    }
    glDeleteTextures(2, boardTextures);
    glDeleteProgram(shaderProgram);

    // unique_ptr pieces are automatically freed when gameState goes out of scope

    logger.log(LogLevel::INFO, "Terminating application...");
    gameplayLogger.log(LogLevel::INFO, "Terminating application...");
    glfwTerminate();
    logger.log(LogLevel::INFO, "Application terminated.");
    gameplayLogger.log(LogLevel::INFO, "Application terminated.");

    return 0;
}
