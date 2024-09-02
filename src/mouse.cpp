#include <GLFW/glfw3.h>
#include "log.h"
#include "config.h"
#include "game/pieces/piece.h"
#include "gameplay.h"
#include "game/gameplay/gameplay_log.h" 
#include "game/logic/logic.h"
#include "memory.h"  // Include memory for storing moves
#include <iostream>
#include <vector>
#include <algorithm>

extern Logger logger;
extern std::vector<Piece*> pieces;
extern Memory gameMemory;  // Declare the global memory object

Piece* selectedPiece = nullptr;
std::string selectedPieceOldPosition;
std::vector<std::pair<int, int>> legalMoves;

// Function to find a piece at a given position
Piece* findPieceAtPosition(int col, int row, const std::vector<Piece*>& pieces) {
    for (auto& piece : pieces) {
        auto [pieceCol, pieceRow] = piece->getPosition();
        if (pieceCol == col && pieceRow == row) {
            return piece;
        }
    }
    return nullptr;
}

// Callback function to handle mouse button events
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        float squareSize = windowWidth < windowHeight ? windowWidth / static_cast<float>(GRID_SIZE) : windowHeight / static_cast<float>(GRID_SIZE);
        float marginX = (windowWidth - GRID_SIZE * squareSize) / 2.0f;
        float marginY = (windowHeight - GRID_SIZE * squareSize) / 2.0f;

        if (xpos >= marginX && xpos <= marginX + GRID_SIZE * squareSize &&
            ypos >= marginY && ypos <= marginY + GRID_SIZE * squareSize) {

            int col = static_cast<int>((xpos - marginX) / squareSize);
            int row = static_cast<int>((ypos - marginY) / squareSize);

            if (selectedPiece == nullptr) {
                selectedPiece = findPieceAtPosition(col, row, pieces);
                if (selectedPiece && isTurnValid(selectedPiece->getColor())) {
                    selectedPieceOldPosition = std::string(1, 'a' + col) + std::to_string(8 - row);
                    legalMoves = selectedPiece->getLegalMoves(col, row);

                    // Log selected piece info
                    std::string pieceColor = (selectedPiece->getColor() == PieceColor::WHITE) ? "White" : "Black";
                    logger.log(LogLevel::DEBUG, "Selected " + pieceColor + " " + getPieceTypeName(selectedPiece) + " with UID: " + std::to_string(selectedPiece->getUID()) +
                               " at position: " + selectedPieceOldPosition);
                    gameplayLogger.log(LogLevel::POSITION, "Selected " + pieceColor + " " + getPieceTypeName(selectedPiece) + " with UID: " + std::to_string(selectedPiece->getUID()) +
                                       " at position: " + selectedPieceOldPosition);
                }
            } else {
                // Check if the selected move is legal
                bool isLegalMove = std::find(legalMoves.begin(), legalMoves.end(), std::make_pair(col, row)) != legalMoves.end();

                if (isLegalMove) {
                    // Store the move in memory before moving the piece
                    std::string finalPosition = std::string(1, 'a' + col) + std::to_string(8 - row);
                    gameMemory.addMove(gameMemory.getMoveHistory().size() / 2 + 1, selectedPiece->getUID(), isTurnValid(PieceColor::WHITE), selectedPieceOldPosition, finalPosition);

                    // Move the piece
                    movePiece(selectedPiece, col, row);
                }

                selectedPiece = nullptr;
                selectedPieceOldPosition.clear();
                legalMoves.clear();
            }
        }
    }
}

void setupMouseCallback(GLFWwindow* window) {
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}
