#include "benchmark.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <string>
#include "log.h"
#include "draw.h"
#include "gameplay.h"

extern Logger logger;

void runBenchmark(
    GLFWwindow*                                     window,
    unsigned int                                    shaderProgram,
    unsigned int                                    boardTextures[2],
    const std::vector<std::unique_ptr<Piece>>&      pieces,
    const std::vector<std::pair<int, int>>&         legalMoves,
    int                                             frames
) {
    logger.log(LogLevel::INFO, "=== BENCHMARK START (" + std::to_string(frames) + " frames) ===");

    glfwSwapInterval(0); // Disable VSync for accurate benchmarking

    double totalFrameUs  = 0.0;
    double totalBoardUs  = 0.0;
    double totalPiecesUs = 0.0;

    for (int i = 0; i < frames && !glfwWindowShouldClose(window); ++i) {
        auto frameStart = std::chrono::high_resolution_clock::now();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Time drawChessboard
        auto t0 = std::chrono::high_resolution_clock::now();
        drawChessboard(shaderProgram, boardTextures, legalMoves);
        glFinish();
        auto t1 = std::chrono::high_resolution_clock::now();

        // Time drawAllPieces
        drawAllPieces(shaderProgram, pieces);
        glFinish();
        auto t2 = std::chrono::high_resolution_clock::now();

        glfwSwapBuffers(window);
        glfwPollEvents();

        auto frameEnd = std::chrono::high_resolution_clock::now();

        totalBoardUs  += std::chrono::duration<double, std::micro>(t1 - t0).count();
        totalPiecesUs += std::chrono::duration<double, std::micro>(t2 - t1).count();
        totalFrameUs  += std::chrono::duration<double, std::micro>(frameEnd - frameStart).count();
    }

    double avgFrame  = totalFrameUs  / frames;
    double avgBoard  = totalBoardUs  / frames;
    double avgPieces = totalPiecesUs / frames;
    double avgFPS    = 1'000'000.0   / avgFrame;

    logger.log(LogLevel::INFO, "=== BENCHMARK RESULTS ===");
    logger.log(LogLevel::INFO, "Frames measured     : " + std::to_string(frames));
    logger.log(LogLevel::INFO, "Avg frame time      : " + std::to_string(avgFrame)  + " us");
    logger.log(LogLevel::INFO, "Avg FPS             : " + std::to_string(avgFPS));
    logger.log(LogLevel::INFO, "Avg drawChessboard  : " + std::to_string(avgBoard)  + " us");
    logger.log(LogLevel::INFO, "Avg drawAllPieces   : " + std::to_string(avgPieces) + " us  (" + std::to_string(100.0 * avgPieces / avgFrame) + "% of frame)");
    logger.log(LogLevel::INFO, "=========================");
}
