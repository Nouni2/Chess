#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "shader.h"
#include "chessboard.h"
#include "game/pieces/king.h"
#include "game/pieces/queen.h"
#include "game/pieces/rook.h"
#include "game/pieces/bishop.h"
#include "game/pieces/knight.h"
#include "game/pieces/pawn.h"

// Window dimensions
const GLuint WIDTH = 1000, HEIGHT = 1000;

void runChessboard(GLFWwindow* window, GLuint shaderProgram) {
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
}

void runTestPiece() {
    Piece* piece = nullptr;
    char choice;
    
    std::cout << "Choose a piece to test (k: King, q: Queen, r: Rook, b: Bishop, n: Knight, p: Pawn): ";
    std::cin >> choice;

    PieceColor color = PieceColor::WHITE;  // Test with a white piece
    int x = 4, y = 4;  // Starting position in the center of the board

    switch (choice) {
        case 'k':
            piece = new King(color);
            break;
        case 'q':
            piece = new Queen(color);
            break;
        case 'r':
            piece = new Rook(color);
            break;
        case 'b':
            piece = new Bishop(color);
            break;
        case 'n':
            piece = new Knight(color);
            break;
        case 'p':
            piece = new Pawn(color);
            break;
        default:
            std::cerr << "Invalid choice!" << std::endl;
            return;
    }

    std::cout << "Score of the piece: " << piece->getScore() << std::endl;

    std::vector<std::pair<int, int>> moves = piece->getLegalMoves(x, y);
    std::cout << "Available moves (1 indicates a possible move):" << std::endl;

    int grid[8][8] = {0};

    for (const auto& move : moves) {
        int mx = move.first;
        int my = move.second;
        if (mx >= 0 && mx < 8 && my >= 0 && my < 8) {
            grid[my][mx] = 1;  // Mark available move with 1
        }
    }

    for (int y = 7; y >= 0; --y) {  // Print in reverse y order to match typical chessboard view
        for (int x = 0; x < 8; ++x) {
            std::cout << grid[y][x] << " ";
        }
        std::cout << std::endl;
    }

    delete piece;  // Clean up the dynamically allocated piece
}

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

    // Run the chessboard display loop
    runChessboard(window, shaderProgram);

    // Once the window is closed, run the console test
    runTestPiece();

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
