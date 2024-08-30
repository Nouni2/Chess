#include <GLFW/glfw3.h>
#include "log.h"
#include "config.h"
#include "game/pieces/piece.h"  
#include "game/gameplay/gameplay_log.h"  // Include the gameplay log for getPieceTypeName
#include "gameplay.h"  // Include for access to pieces vector
#include <iostream>

extern Logger logger;
extern std::vector<Piece*> pieces; // Access the vector of pieces from gameplay


// Function to find a piece at a given position
Piece* findPieceAtPosition(int col, int row) {
    logger.log(LogLevel::DEBUG, "Searching for piece at position (" + std::to_string(col) + ", " + std::to_string(row) + ")");
    
    // Log the number of elements in the pieces vector
    logger.log(LogLevel::DEBUG, "Number of pieces in vector: " + std::to_string(pieces.size()));
    for (auto& piece : pieces) {
        logger.log(LogLevel::DEBUG, "Entering piece position checking loop");
        auto [pieceCol, pieceRow] = piece->getPosition();
        logger.log(LogLevel::DEBUG, "Checking piece with UID: " + std::to_string(piece->getUID()) + 
                                    " at position (" + std::to_string(pieceCol) + ", " + std::to_string(pieceRow) + ")");
        
        if (pieceCol == col && pieceRow == row) {
            logger.log(LogLevel::DEBUG, "Piece found at position (" + std::to_string(col) + ", " + std::to_string(row) + 
                                        ") with UID: " + std::to_string(piece->getUID()));
            return piece;
        }
    }
    
    logger.log(LogLevel::DEBUG, "No piece found at position (" + std::to_string(col) + ", " + std::to_string(row) + ")");
    return nullptr;
}


// Callback function to handle mouse button events
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // Get the cursor position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Get the window dimensions
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        // Calculate the size of each square based on the chessboard size and grid size
        float squareSize = windowWidth < windowHeight ? windowWidth / static_cast<float>(GRID_SIZE) : windowHeight / static_cast<float>(GRID_SIZE);

        // Calculate the margins (in case the chessboard is centered and there are black borders)
        float marginX = (windowWidth - GRID_SIZE * squareSize) / 2.0f;
        float marginY = (windowHeight - GRID_SIZE * squareSize) / 2.0f;

        // Check if the click is within the chessboard area
        if (xpos >= marginX && xpos <= marginX + GRID_SIZE * squareSize &&
            ypos >= marginY && ypos <= marginY + GRID_SIZE * squareSize) {

            // Calculate the grid position (row and column)
            int col = static_cast<int>((xpos - marginX) / squareSize);
            int row = static_cast<int>((ypos - marginY) / squareSize);

            // Convert row and column to chess notation (e.g., 'f3')
            char colChar = 'a' + col;
            int rowNumber = GRID_SIZE - row;

            std::string square = std::string(1, colChar) + std::to_string(rowNumber);

            // Check if the square is occupied
            Piece* piece = findPieceAtPosition(col, row);
            if (piece) {
                // The square is occupied
                std::string pieceType = getPieceTypeName(piece);  // Use the function correctly
                std::string pieceColor = (piece->getColor() == PieceColor::WHITE) ? "White" : "Black";
                int pieceUID = piece->getUID();

                std::cout << "Square " << square << " is occupied by a " << pieceColor << " " << pieceType 
                          << " with UID: " << pieceUID << std::endl;
                logger.log(LogLevel::DEBUG, "Square " + square + " is occupied by a " + pieceColor + " " + pieceType + 
                                          " with UID: " + std::to_string(pieceUID));
            } else {
                // The square is not occupied
                std::cout << "Square " << square << " is not occupied." << std::endl;
                logger.log(LogLevel::DEBUG, "Square " + square + " is not occupied.");
            }
        } else {
            // Click was outside the chessboard area
            std::cout << "Click was outside the chessboard area." << std::endl;
            logger.log(LogLevel::DEBUG, "Left mouse button clicked outside the chessboard area.");
        }
    }
}

// Function to set up the mouse callback
void setupMouseCallback(GLFWwindow* window) {
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}
