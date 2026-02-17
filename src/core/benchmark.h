#pragma once
#include <vector>
#include <memory>
#include <utility>

struct GLFWwindow;
class Piece;

void runBenchmark(
    GLFWwindow*                                     window,
    unsigned int                                    shaderProgram,
    unsigned int                                    boardTextures[2],
    const std::vector<std::unique_ptr<Piece>>&      pieces,
    const std::vector<std::pair<int, int>>&         legalMoves,
    int                                             frames = 500
);
